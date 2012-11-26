namespace Cursor3
{
    using System;
    using System.Globalization;
    using System.IO;
    using System.Windows;
    using System.Windows.Media;
    using System.Windows.Media.Imaging;
    using Microsoft.Kinect;
    using System.Runtime.InteropServices;
    using System.Windows.Controls;
    using System.Diagnostics;
    using Emgu.CV;
    using Emgu.CV.CvEnum;
    using Emgu.CV.Structure;
    using System.Drawing;
    using System.Drawing.Imaging;
    using System.Collections.Generic;

    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// Utilizes OpenCV for contour and convex hull detection
    /// </summary>
    public partial class MainWindow : Window
    {
        private KinectSensor sensor;
        // Array of depthPixel objects
        private short[] depthPixels;

        // Depth Limit
        private int DLimit = 1000;
        // Detect touching the "virtual screen"
        private bool touching = false;
        private bool detected = false;

        // For location tracking
        private int xLoc = 0;
        private int yLoc = 0;

        // Gesture command
        Cursor3.Gesture gest;

        // Frame image
        Image<Bgr, Byte> img;
        Image<Gray, Byte> gray;

        // Initialization 
        public MainWindow()
        {
            InitializeComponent();
        }

        private void WindowLoaded(object sender, RoutedEventArgs e)
        {
            // Look for a sensor candidate 
            foreach (var potentialSensor in KinectSensor.KinectSensors)
            {
                if (potentialSensor.Status == KinectStatus.Connected)
                {
                    this.sensor = potentialSensor;
                    break;
                }
            }

            if (null != this.sensor)
            {
                // Enable the collection of data
                this.sensor.DepthStream.Enable(DepthImageFormat.Resolution640x480Fps30);
                // Allocate space to put the depth pixels we'll receive
                this.depthPixels = new short[this.sensor.DepthStream.FramePixelDataLength];
                // Start gesture command
                gest = new Cursor3.Gesture(this);


                // Activate main loop
                this.sensor.DepthFrameReady += this.SensorDepthFrameReady;


                // Start the sensor
                try
                {
                    this.sensor.Start();
                }
                catch (IOException)
                {
                    this.sensor = null;
                }
            }

            // No sensor found
            if (null == this.sensor)
            {
                this.statusBarText.Text = "No Kinect Found";
            }
        }

        private void WindowClosing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            if (null != this.sensor)
            {
                this.sensor.Stop();
            }
        }

        private void SensorDepthFrameReady(object sender, DepthImageFrameReadyEventArgs e)
        {
            using (DepthImageFrame depthFrame = e.OpenDepthImageFrame())
            {
                if (depthFrame != null)
                {
                    // Copy the pixel data from the image to a temporary array
                    depthFrame.CopyPixelDataTo(this.depthPixels);
                    // Create the image
                    this.img = new Image<Bgr, byte>(640, 480, new Bgr(0, 0, 0));
                    // Reset text
                    this.text.Text = "";

                    // Segment out the hands to boolean values in colorPixels
                    this.segmentHands();

                    // Gray image
                    this.gray = img.Convert<Gray, Byte>();

                    // Perform various actions if the user is touching the "screen"
                    if (this.touching)
                    {
                        // Find the fingers
                        int numFingers = this.findFingers();
                        this.setText("Number of Fingers: " + Convert.ToString(numFingers) + "\n");

                        // Move the cursor
                        if (this.xLoc != 0 && this.yLoc != 0)
                        {
                            if (!this.detected)
                            {
                                this.detected = true;
                                gest.setHand(this.xLoc, this.yLoc);
                            }
                            gest.handMovement(this.xLoc, this.yLoc, numFingers);
                        }
                        // Determine if a click is registered
                        gest.clickMouse(numFingers);
                    }
                    else
                    {
                        this.xLoc = 0;
                        this.yLoc = 0;
                        gest.reset();
                    }

                    // Get the image data
                    BitmapSource source = ToBitmapSource(img);

                    // Image source is our source
                    this.Image.Source = source;
                }
            }
        }





        // Next two static functions borrowed code from emgu
        /// <summary>
        /// Delete a GDI object
        /// </summary>
        /// <param name="o">The poniter to the GDI object to be deleted</param>
        /// <returns></returns>
        [DllImport("gdi32")]
        private static extern int DeleteObject(IntPtr o);

        /// <summary>
        /// Convert an IImage to a WPF BitmapSource. The result can be used in the Set Property of Image.Source
        /// </summary>
        /// <param name="image">The Emgu CV Image</param>
        /// <returns>The equivalent BitmapSource</returns>
        public static BitmapSource ToBitmapSource(IImage image)
        {
            using (System.Drawing.Bitmap source = image.Bitmap)
            {
                IntPtr ptr = source.GetHbitmap(); //obtain the Hbitmap

                BitmapSource bs = System.Windows.Interop.Imaging.CreateBitmapSourceFromHBitmap(
                    ptr,
                    IntPtr.Zero,
                    Int32Rect.Empty,
                    System.Windows.Media.Imaging.BitmapSizeOptions.FromEmptyOptions());

                DeleteObject(ptr); //release the HBitmap
                return bs;
            }
        }

        public static PointF pointToPointF(System.Drawing.Point p)
        {
            return new PointF(p.X, p.Y);
        }



        // Segmenting out the points beyond the screen distance
        // TO DO: Implement an unsupervised learning algorithm (k means?) to segment out two hands
        // Also maybe do a depth segmentation to get rid of arms (would allow us to get palm points easily as well)
        private void segmentHands()
        {
            // Note to self: Don't use properties inside loops for C#, it'll lower performance
            this.touching = false;
            byte[, ,] data = this.img.Data;
            for (int j = 0; j < 480; j += 1)
            {
                for (int i = 0; i < 640; i += 1)
                {

                    // discard the portion of the depth that contains only the player index
                    int depth = ((ushort)this.depthPixels[i + 640*j] >> DepthImageFrame.PlayerIndexBitmaskWidth);

                    int secondLayer = this.DLimit + 750;

                    // Contact points orange
                    if (depth < this.DLimit)
                    {
                        data[j, i, 0] = 255;
                        data[j, i, 1] = 255;
                        data[j, i, 2] = 255;

                        this.touching = true;
                    }
                }
                
                    
            }
            if (!this.touching)
            {
                this.detected = false;
            }
          
        }




        // Combines finding the contour, convex hull, and isolating the fingers
        private int findFingers()
        {
            // The number of fingers
            int numFingers = 0;

            // Initiate storage
            MemStorage contourStorage = new MemStorage();
            MemStorage hullStorage = new MemStorage();

            // Get the contour candidates and accept the one with the largest area
            Contour<System.Drawing.Point> contours = null;
            Contour<System.Drawing.Point> midContour = null;
            Contour<System.Drawing.Point> finalContour = null;
            double finalArea = 0;
            double currArea = 0;
            for (contours = this.gray.FindContours(Emgu.CV.CvEnum.CHAIN_APPROX_METHOD.CV_CHAIN_APPROX_SIMPLE, Emgu.CV.CvEnum.RETR_TYPE.CV_RETR_LIST, contourStorage); contours != null; contours = contours.HNext)
            {
                currArea = contours.Area;
                if (currArea > finalArea)
                {
                    finalArea = currArea;
                    midContour = contours;
                }
                
            }
            if (midContour == null)
            {
                return 0;
            }
            finalContour = midContour.ApproxPoly(midContour.Perimeter * .0025, contourStorage);
            this.img.DrawPolyline(finalContour.ToArray(), true, new Bgr(255.0, 255.0, 0.0), 2);
            

            // Get the convexity defects
            Seq<MCvConvexityDefect> defectSeq = finalContour.GetConvexityDefacts(contourStorage, ORIENTATION.CV_CLOCKWISE);
            MCvConvexityDefect[] defectArray = defectSeq.ToArray();

            
            // Find the fingertips
            /*
             * Summary of algorithm: 
             * 1. Find points that are bounded on two sides with convexity defects
             * 2. Find the angle between the two lines drawn between corner points of the convexity defect (fingers are like triangles)
             * 3. Find length of said lines
             * 4. Filter based off of angle and length
            */
            PointF startPoint;
            PointF depthPoint;
            PointF endPoint = new PointF();
            LineSegment2D startDepthLine = new LineSegment2D();
            LineSegment2D depthEndLine = new LineSegment2D();
            List<PointF> fingerPoints = new List<PointF>();

            List<PointF> endPoints = new List<PointF>();
            List<LineSegment2D> endLines = new List<LineSegment2D>();

            for (int i = 0; i < defectArray.Length; i++)
            {
                endPoint = new PointF((float)defectArray[i].EndPoint.X, (float)defectArray[i].EndPoint.Y);
                depthEndLine = new LineSegment2D(defectArray[i].DepthPoint, defectArray[i].EndPoint);
                endPoints.Add(endPoint);
                endLines.Add(depthEndLine);
            }

            for (int i = 0; i < defectArray.Length; i++)
            {
                startPoint = new PointF((float)defectArray[i].StartPoint.X, (float)defectArray[i].StartPoint.Y);
                depthPoint = new PointF((float)defectArray[i].DepthPoint.X, (float)defectArray[i].DepthPoint.Y);
                startDepthLine = new LineSegment2D(defectArray[i].StartPoint, defectArray[i].DepthPoint);

                bool foundSecondLine = false;
                double distance = 0;
                for (int j = 0; j < endPoints.Count; j++)
                {
                    endPoint = endPoints[j];
                    distance = ptDist(startPoint.X, endPoint.X, startPoint.Y, endPoint.Y);
                    if (distance < 20)
                    {
                        depthEndLine = endLines[j];
                        foundSecondLine = true;
                        break;
                    }
                }

                if (foundSecondLine)
                {
                    double[] v1 = { startDepthLine.P2.X - startDepthLine.P1.X, startDepthLine.P2.Y - startDepthLine.P1.Y };
                    double[] v2 = { depthEndLine.P1.X - depthEndLine.P2.X, depthEndLine.P1.Y - depthEndLine.P2.Y };
                    double v1Len = ptDist(startDepthLine.P2.X, startDepthLine.P1.X, startDepthLine.P2.Y, startDepthLine.P1.Y);
                    double v2Len = ptDist(depthEndLine.P1.X, depthEndLine.P2.X, depthEndLine.P1.Y, depthEndLine.P2.Y);

                    double angle = findAngle(v1, v2);

                    CircleF startCircle = new CircleF(startPoint, 5);
                    CircleF depthCircle = new CircleF(depthPoint, 5);
                    CircleF endCircle = new CircleF(endPoint, 5);
                    CircleF avgCircle = new CircleF(new PointF((startPoint.X + endPoint.X) / 2, (startPoint.Y + endPoint.Y) / 2), 5);

                    if (angle < 1.1 && v1Len > 15 && v2Len > 15)
                    {
                        numFingers++;
                        fingerPoints.Add(new PointF((startPoint.X + endPoint.X) / 2, (startPoint.Y + endPoint.Y) / 2));
                        img.Draw(avgCircle, new Bgr(System.Drawing.Color.Green), 2);
                        //img.Draw(startDepthLine, new Bgr(System.Drawing.Color.Magenta), 2);
                        //img.Draw(depthEndLine, new Bgr(System.Drawing.Color.Navy), 2);
                    }

                }
            }

            // Get a reference point for the cursor, needs improvement
            if (finalContour.GetConvexHull(ORIENTATION.CV_CLOCKWISE).ToArray().Length != 0)
            {
                System.Drawing.PointF[] hullPts = Array.ConvertAll<System.Drawing.Point, PointF>(finalContour.GetConvexHull(ORIENTATION.CV_CLOCKWISE).ToArray(), pointToPointF);
                CircleF minCircle = Emgu.CV.PointCollection.MinEnclosingCircle(hullPts);
                PointF center = minCircle.Center;
                img.Draw(new CircleF(center, 2), new Bgr(System.Drawing.Color.Red), 2);
                this.xLoc = (int)center.X;
                this.yLoc = (int)center.Y;
            }

            return numFingers;


            /*
             * This version looked for fingertips based off of points on the convex hull and whether corresponding points on the contour were alligned 
             * Very jumpy due to imperfections in the hull
             * 
             
            // System.Drawing.Point[] hullPts = finalContour.GetConvexHull(Emgu.CV.CvEnum.ORIENTATION.CV_CLOCKWISE, hullStorage).ToArray();
            // this.img.DrawPolyline(hullPts, true, new Bgr(0.0, 255.0, 255.0), 1);

            // Filter out points on the hull that are too close to each other
            
            List<System.Drawing.Point> hullPointsPost = new List<System.Drawing.Point>();
            hullPointsPost.Add(hullPts[0]);
            bool add;
            for (int i = 1; i < hullPts.Length; i++)
            {
                add = true;
                foreach (System.Drawing.Point inPt in hullPointsPost)
                {
                    if (ptDist(hullPts[i].X, inPt.X, hullPts[i].Y, inPt.Y) < 15)
                    {
                        add = false;
                    }
                }
                if (add)
                {
                    hullPointsPost.Add(hullPts[i]);
                }
            }
            
            List<System.Drawing.PointF> midPts = new List<System.Drawing.PointF>();
            List<System.Drawing.Point> fingerPts = new List<System.Drawing.Point>();
            foreach (System.Drawing.Point p in hullPointsPost)
            {
                int depth = (ushort)this.depthPixels[p.X + 640 * p.Y] >> DepthImageFrame.PlayerIndexBitmaskWidth;
                int closestIndex = closestPt(p, finalContour);
                System.Drawing.Point closest = finalContour[closestIndex];
                System.Drawing.Point left;
                System.Drawing.Point right;
                int step = 3;
                if (closestIndex >= step)
                {
                    left = finalContour[closestIndex - step];
                    if (closestIndex < finalContour.ToArray().Length - step)
                    {
                        right = finalContour[closestIndex + step];
                    }
                    else
                    {
                        right = finalContour[finalContour.ToArray().Length - closestIndex + step];
                    }

                }
                else
                {
                    left = finalContour[finalContour.ToArray().Length + closestIndex - step];
                    if (closestIndex < finalContour.ToArray().Length - step)
                    {
                        right = finalContour[closestIndex + step];
                    }
                    else
                    {
                        right = finalContour[finalContour.ToArray().Length - closestIndex + step];
                    }
                }

                //img.Draw(new CircleF(left, 3), new Bgr(255.0, 0.0, 255.0), 5);
                //img.Draw(new CircleF(right, 3), new Bgr(255.0, 0.0, 255.0), 5);

                int lx = left.X;
                int ly = left.Y;
                int rx = right.X;
                int ry = right.Y;
                int mx = (left.X + right.X) / 2;
                int my = (left.Y + right.Y) / 2;
                double pseudoDist = ptDist(closest.X, mx, closest.Y, my);
                
                if (pseudoDist > 25 && depth < this.minDepth + 75)
                {
                    midPts.Add(new System.Drawing.Point(mx, my));
                    fingerPts.Add(p);
                }
                

                // Text for debugging
                text.Text = "Current minDepth: " + Convert.ToString(minDepth) + "\n";
                text.Text += "Current Depth: " + Convert.ToString(depth);

            }

            foreach (System.Drawing.Point pt in fingerPts)
            {
                img.Draw(new CircleF(pt, 3), new Bgr(0.0, 0.0, 255.0), 5);
            }
            foreach (System.Drawing.PointF pt in midPts)
            {
                img.Draw(new CircleF(pt, 3), new Bgr(0.0, 80.0, 255.0), 5);
            }
            */
            
        }

        // Distance between two points
        private static double ptDist(double x1, double x2, double y1, double y2)
        {
            return Math.Sqrt(Math.Pow(x1 - x2, 2) + Math.Pow(y1 - y2, 2));
        }

        // Finds the List of all points a given distance away from the refernce point pt1
        private static List<System.Drawing.Point> ptAtDist(System.Drawing.Point pt1, Contour<System.Drawing.Point> ptList, double dist)
        {
            double epsilon = 4;
            List<System.Drawing.Point> toReturn = new List<System.Drawing.Point>();
            foreach (System.Drawing.Point pt2 in ptList)
            {
                double distance = ptDist(pt1.X, pt2.X, pt1.Y, pt2.Y);
                if (distance < dist + epsilon && distance > dist - epsilon)
                {
                    toReturn.Add(pt2);
                }
            }

            return toReturn;
        }

        // Finds the index of the point in ptList closest to the given point pt1
        private static int closestPt(System.Drawing.Point pt1, Contour<System.Drawing.Point> ptList)
        {
            int dist = Int32.MaxValue;
            int closestIndex = 0;
            System.Drawing.Point closest = new System.Drawing.Point(0, 0);
            for (int i = 0; i < ptList.ToArray().Length; i++)
            {
                System.Drawing.Point pt2 = ptList[i];
                if (ptDist(pt1.X, pt2.X, pt1.Y, pt2.Y) < dist)
                {
                    dist = (int) ptDist(pt1.X, pt2.X, pt1.Y, pt2.Y);
                    closest = pt2;
                    closestIndex = i;
                }
            }
            return closestIndex;
        }

        // Finds angle between two vectors
        private double findAngle(double[] x, double[] y)
        {
            double x1 = x[0];
            double x2 = x[1];
            double y1 = y[0];
            double y2 = y[1];
            double inner = x1 * y1 + x2 * y2;
            double magX = Math.Sqrt(x1 * x1 + x2 * x2);
            double magY = Math.Sqrt(y1 * y1 + y2 * y2);
            return Math.Acos(inner / magX / magY);
        }

        // Sets the text
        public void setText(String txt)
        {
            text.Text += txt;
        }

    }
}
