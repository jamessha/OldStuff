namespace Kinect
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

    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// DISCLAIMER: The initialization procedures such as searching for a kinect, starting feed, etc, are imported from demos
    /// Does not work: numFingers
    /// </summary>
    public partial class MainWindow : Window
    {
        private KinectSensor sensor;
        // Bitmap for image
        private WriteableBitmap colorBitmap;
        // Array of depthPixel objects
        private short[] depthPixels;
        // Storing pixels converted to color
        private byte[] colorPixels;
        // Storing the outline
        private int[] outlineX;
        private int[] outlineY;
        private int outlineInd;
        // Closest points
        int[] closest;
        // Depth Limit
        int DLimit;
        // Detect touching the "virtual screen"
        bool touching;


        // FOR CONTROL
        [DllImport("user32.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        public static extern void keybd_event(byte bVk, byte bScan, int dwFlags, int dwExtraInfo);
        private const int KEYEVENTF_EXTENDEDKEY = 0x0001; //Key down flag
        private const int KEYEVENTF_KEYUP = 0x0002; //Key up flag
        private Stopwatch Timer = new Stopwatch();
        private int DELAY = 1000;
        private int lastX = 0;
        private int lastY = 0;
        private int vhit1 = 200;
        private int vhit2 = 450;
        private int hhit1 = 240;
        private int vhitm = 320;

        //rotate entire cube keys
        private const int ROTATE_CUBE_RIGHT_KEY = 0x44; //d
        private const int ROTATE_CUBE_LEFT_KEY = 0x41; //a
        private const int ROTATE_CUBE_UP_KEY = 0x57; //w
        private const int ROTATE_CUBE_DOWN_KEY = 0x53; //s

        //rotate front face, right face, and possibly top face keys
        private const int FRONT_CLOCKWISE_KEY = 0x25; //left
        private const int FRONT_COUNTERCLOCKWISE_KEY = 0x27; //right
        private const int RIGHT_INTO_UP_KEY = 0x26; //up
        private const int RIGHT_OUTOF_DOWN_KEY = 0x28; //down



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
                // Allocate space to put the color pixels we'll create
                this.colorPixels = new byte[this.sensor.DepthStream.FramePixelDataLength * sizeof(int)];
                // Create a colorBitmap
                this.colorBitmap = new WriteableBitmap(this.sensor.DepthStream.FrameWidth, this.sensor.DepthStream.FrameHeight, 96.0, 96.0, PixelFormats.Bgr32, null);
                // Display comes from the bitmap
                this.Image.Source = this.colorBitmap;
                // Timer
                this.Timer.Start();
                // Depth Limit
                this.DLimit = 1000;
                this.touching = false;

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
                    // New array for the outline pixels
                    this.outlineX = new int[this.sensor.DepthStream.FramePixelDataLength * sizeof(int)];
                    this.outlineY = new int[this.sensor.DepthStream.FramePixelDataLength * sizeof(int)];
                    this.outlineInd = 0;
                    // Closest point
                    this.closest = new int[this.sensor.DepthStream.FramePixelDataLength * sizeof(int)];
                    this.Timer.Start();
                    // Segment out the hands to boolean values in colorPixels
                    this.segmentHands();
                    //this.outlineHands();
                    //this.sortBoundary();
                    //this.findFingers();

                    

                    // Write the pixel data into our bitmap
                    this.colorBitmap.WritePixels(
                        new Int32Rect(0, 0, this.colorBitmap.PixelWidth, this.colorBitmap.PixelHeight),
                        this.colorPixels,
                        this.colorBitmap.PixelWidth * sizeof(int),
                        0);
                }
            }
        }

        private void segmentHands()
        {
            short closestPixel = 0;
            int closestDepth1 = 0;
            int colorPixelIndex = 0;
            int closestX = 0;
            int closestY = 0;


            for (int j = 0; j < 480; j += 1)
            {
                for (int i = 0; i < 640; i += 1)
                {

                    // discard the portion of the depth that contains only the player index
                    int depth = ((ushort)this.depthPixels[i + 640*j] >> DepthImageFrame.PlayerIndexBitmaskWidth);

                    // find the closest pixel
                    if (closestPixel == 0)
                    {
                        closestPixel = this.depthPixels[i + 640*j];
                        closestDepth1 = depth;
                        closestX = i;
                        closestY = j;
                    }
                    else
                    {
                        if (depth < closestDepth1)
                        {
                            closestPixel = this.depthPixels[i + 640 * j];
                            closestDepth1 = depth;
                            closestX = i;
                            closestY = j;
                        }
                    }

                    colorPixelIndex += 4;
                }
            }

            colorPixelIndex = 0;
            for (int j = 0; j < 480; j += 1)
            {
                for (int i = 0; i < 640; i += 1)
                {

                    // discard the portion of the depth that contains only the player index
                    int depth = ((ushort)this.depthPixels[i + 640*j] >> DepthImageFrame.PlayerIndexBitmaskWidth);

                        
                        if (depth < this.DLimit)
                        {
                            // Write out blue byte
                            this.colorPixels[colorPixelIndex++] = 0;

                            // Write out green byte
                            this.colorPixels[colorPixelIndex++] = 127;

                            // Write out red byte                        
                            this.colorPixels[colorPixelIndex++] = 255;

                            colorPixelIndex++;

                            this.touching = true;

                        }
                        else if (depth < this.DLimit + 750)
                        {
                            // Write out blue byte
                            this.colorPixels[colorPixelIndex++] = 255;

                            // Write out green byte
                            this.colorPixels[colorPixelIndex++] = 127;

                            // Write out red byte                        
                            this.colorPixels[colorPixelIndex++] = 0;

                            colorPixelIndex++;
                        }
                        else
                        {
                            // Write out blue byte
                            this.colorPixels[colorPixelIndex++] = 0;

                            // Write out green byte
                            this.colorPixels[colorPixelIndex++] = 0;

                            // Write out red byte                        
                            this.colorPixels[colorPixelIndex++] = 0;

                            colorPixelIndex++;
                        }
                    }
                
                    
            }

            for (int j = 0; j < 480 * 4 - 3; j += 4)
            {
                this.colorPixels[(vhit1 * 4 + 0) + 640 * (j + 0)] = 0;
                this.colorPixels[(vhit1 * 4 + 1) + 640 * (j + 0)] = 255;
                this.colorPixels[(vhit1 * 4 + 2) + 640 * (j + 0)] = 0;
                this.colorPixels[(vhit2 * 4 + 0) + 640 * (j + 0)] = 0;
                this.colorPixels[(vhit2 * 4 + 1) + 640 * (j + 0)] = 255;
                this.colorPixels[(vhit2 * 4 + 2) + 640 * (j + 0)] = 0;
                this.colorPixels[(vhitm * 4 + 0) + 640 * (j + 0)] = 0;
                this.colorPixels[(vhitm * 4 + 1) + 640 * (j + 0)] = 255;
                this.colorPixels[(vhitm * 4 + 2) + 640 * (j + 0)] = 255;
            }
            for (int i = 0; i < 640 * 4; i += 4)
            {
                this.colorPixels[(i + 0) + 640 * (hhit1 * 4 + 0)] = 0;
                this.colorPixels[(i + 1) + 640 * (hhit1 * 4 + 0)] = 255;
                this.colorPixels[(i + 2) + 640 * (hhit1 * 4 + 0)] = 0;
            }

            if (closestX > 7 && closestX < 640 - 7 && closestY > 7 && closestY < 480 - 7)
            {
                for (int i = closestX - 7; i < closestX + 7; i++)
                {
                    for (int j = closestY - 7; j < closestY + 7; j++)
                    {
                        if (!this.touching)
                        {
                            this.colorPixels[(i * 4 + 0) + 640 * (j * 4 + 0)] = 255;
                            this.colorPixels[(i * 4 + 1) + 640 * (j * 4 + 0)] = 255;
                            this.colorPixels[(i * 4 + 2) + 640 * (j * 4 + 0)] = 255;
                        }
                        else
                        {
                            this.colorPixels[(i * 4 + 0) + 640 * (j * 4 + 0)] = 0;
                            this.colorPixels[(i * 4 + 1) + 640 * (j * 4 + 0)] = 0;
                            this.colorPixels[(i * 4 + 2) + 640 * (j * 4 + 0)] = 255;
                        }
                    }
                }
            }

            performAct(closestX, closestY);
        }


        private void performAct(int closestX, int closestY)
        {
            if (this.touching && this.Timer.ElapsedMilliseconds >= this.DELAY)
            {

                if (this.lastX < vhit1 && closestX >= vhit1)
                {
                    keybd_event(ROTATE_CUBE_RIGHT_KEY, 0, KEYEVENTF_EXTENDEDKEY, 0);
                    keybd_event(ROTATE_CUBE_RIGHT_KEY, 0, KEYEVENTF_KEYUP, 0);
                    this.Timer.Reset();
                    this.Timer.Start();
                }

                else if (this.lastX > vhit1 && closestX <= vhit1)
                {
                    keybd_event(ROTATE_CUBE_LEFT_KEY, 0, KEYEVENTF_EXTENDEDKEY, 0);
                    keybd_event(ROTATE_CUBE_LEFT_KEY, 0, KEYEVENTF_KEYUP, 0);
                    this.Timer.Reset();
                    this.Timer.Start();
                }

                else if (this.lastY > hhit1 && closestY <= hhit1 && closestX < vhitm)
                {
                    keybd_event(ROTATE_CUBE_UP_KEY, 0, KEYEVENTF_EXTENDEDKEY, 0);
                    keybd_event(ROTATE_CUBE_UP_KEY, 0, KEYEVENTF_KEYUP, 0);
                    this.Timer.Reset();
                    this.Timer.Start();
                }

                else if (this.lastY < hhit1 && closestY >= hhit1 && closestX < vhitm)
                {
                    keybd_event(ROTATE_CUBE_DOWN_KEY, 0, KEYEVENTF_EXTENDEDKEY, 0);
                    keybd_event(ROTATE_CUBE_DOWN_KEY, 0, KEYEVENTF_KEYUP, 0);
                    this.Timer.Reset();
                    this.Timer.Start();
                }


                else if (this.lastX < vhit2 && closestX >= vhit2)
                {
                    keybd_event(FRONT_COUNTERCLOCKWISE_KEY, 0, KEYEVENTF_EXTENDEDKEY, 0);
                    keybd_event(FRONT_COUNTERCLOCKWISE_KEY, 0, KEYEVENTF_KEYUP, 0);
                    this.Timer.Reset();
                    this.Timer.Start();
                }

                else if (this.lastX > vhit2 && closestX <= vhit2)
                {
                    keybd_event(FRONT_CLOCKWISE_KEY, 0, KEYEVENTF_EXTENDEDKEY, 0);
                    keybd_event(FRONT_CLOCKWISE_KEY, 0, KEYEVENTF_KEYUP, 0);
                    this.Timer.Reset();
                    this.Timer.Start();
                }

                else if (this.lastY > hhit1 && closestY <= hhit1 && closestX > vhitm)
                {
                    keybd_event(RIGHT_INTO_UP_KEY, 0, KEYEVENTF_EXTENDEDKEY, 0);
                    keybd_event(RIGHT_INTO_UP_KEY, 0, KEYEVENTF_KEYUP, 0);
                    this.Timer.Reset();
                    this.Timer.Start();
                }

                else if (this.lastY < hhit1 && closestY >= hhit1 && closestX > vhitm)
                {
                    keybd_event(RIGHT_OUTOF_DOWN_KEY, 0, KEYEVENTF_EXTENDEDKEY, 0);
                    keybd_event(RIGHT_OUTOF_DOWN_KEY, 0, KEYEVENTF_KEYUP, 0);
                    this.Timer.Reset();
                    this.Timer.Start();
                }

                this.touching = false;
            }
            

            this.lastX = closestX;
            this.lastY = closestY;
        }

        private void outlineHands()
        {
            bool prevWhite = false;
            bool prevBlack = true;
            bool prevGray = false;
            for (int j = 0; j < 480 * 4 - 3; j += 1)
            {
                for (int i = 0; i < 640 * 4; i += 4)
                {
                    int currR = this.colorPixels[(i + 0) + 640 * (j + 0)];
                    int currG = this.colorPixels[(i + 1) + 640 * (j + 0)];
                    int currB = this.colorPixels[(i + 2) + 640 * (j + 0)];
                    bool currBlack;
                    bool currGray;
                    bool currWhite;

                    int currSum = currR + currG + currB;
                    currBlack = currSum == 255 * 3;
                    currGray = currSum == 255 * 2;
                    currWhite = currSum == 0;

                    if (prevBlack && currWhite)
                    {
                        this.colorPixels[(i + 0) + 640 * (j + 0)] = 0;
                        this.colorPixels[(i + 1) + 640 * (j + 0)] = 255;
                        this.colorPixels[(i + 2) + 640 * (j + 0)] = 255;

                        prevBlack = false;
                        prevGray = true;

                        this.outlineX[this.outlineInd] = i;
                        this.outlineY[this.outlineInd] = j;
                        this.outlineInd++;
                    }
                    else if (prevGray && currWhite)
                    {

                        prevWhite = true;
                        prevGray = false;
                    }
                    else if (prevWhite && currWhite)
                    {
                    }
                    else if (prevWhite && currBlack)
                    {
                        this.colorPixels[(i + 0) + 640 * (j + 0)] = 0;
                        this.colorPixels[(i + 1) + 640 * (j + 0)] = 255;
                        this.colorPixels[(i + 2) + 640 * (j + 0)] = 255;

                        prevWhite = false;
                        prevGray = true;

                        this.outlineX[this.outlineInd] = i;
                        this.outlineY[this.outlineInd] = j;
                        this.outlineInd++;
                    }
                    else if (prevGray && currBlack)
                    {
                        prevGray = false;
                        prevBlack = true;
                    }
                    else
                    {
                        this.colorPixels[(i + 0) + 640 * (j + 0)] = 255;
                        this.colorPixels[(i + 1) + 640 * (j + 0)] = 255;
                        this.colorPixels[(i + 2) + 640 * (j + 0)] = 255;
                    }


                }
            }
        }

        // Finds the angle between two vectors [x1, x2] and [y1, y2] using cos(theta) = <x, y>/|x|/|y|
        private double findAngle(int[] x, int[] y)
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

        private int[] findCentroid(int[] x, int[] y)
        {
            int xAvg = 0;
            int yAvg = 0;
            for (int i = 0; i < x.Length; i++)
            {
                xAvg += x[i];
            }
            for (int i = 0; i < y.Length; i++)
            {
                yAvg += y[i];
            }
            xAvg = xAvg / x.Length;
            yAvg = yAvg / y.Length;
            int[] toReturn = {xAvg, yAvg};
            return toReturn;

        }

        private double findDistance(int[] x, int[] y)
        {
            return Math.Sqrt(Math.Pow((x[1] - x[0]), 2) + Math.Pow((y[1] - y[0]), 2));
        }

        private double findDistance(int x1, int x2, int y1, int y2)
        {
            return Math.Sqrt(Math.Pow((x1 - x2), 2) + Math.Pow((y1 - y2), 2));
        }

        // Returns the sum of the RGB values of a pixel
        private int getColor(int x, int y)
        {
            int currR = this.colorPixels[(x + 0) + 640 * (y + 0)];
            int currG = this.colorPixels[(x + 1) + 640 * (y + 0)];
            int currB = this.colorPixels[(x + 2) + 640 * (y + 0)];

            return currR + currG + currB;
        }

        // Sorts for a boundary curve
        private void sortBoundary()
        {
            int newInd = 0;
            int[] newOutlineX = new int[this.outlineInd];
            int[] newOutlineY = new int[this.outlineInd];
            int prevY = this.outlineY[0];
            for (int i = 1; i < this.outlineInd; i++)
            {
                if (this.outlineY[i] > prevY)
                {
                    prevY = this.outlineY[i];
                    newOutlineX[newInd] = this.outlineX[i];
                    newOutlineY[newInd] = this.outlineY[i];
                    newInd++;
                }
            }
            this.outlineX = newOutlineX;
            this.outlineY = newOutlineY;
            this.outlineInd = newInd;
        }

        // Using k-curvature to find fingers
        private void findFingers()
        {
            for (int i = 2; i < this.outlineInd - 2; i++)
            {
                int x0 = this.outlineX[i];
                int y0 = this.outlineY[i];
                int x1 = this.outlineX[i - 2];
                int y1 = this.outlineY[i - 2];
                int x2 = this.outlineX[i + 2];
                int y2 = this.outlineY[i + 2];
                int v1x = Math.Abs(x1 - x0);
                int v1y = Math.Abs(y1 - y0);
                int v2x = Math.Abs(x2 - x0);
                int v2y = Math.Abs(y2 - y0);
                int[] vec1 = { v1x, v1y };
                int[] vec2 = { v2x, v2y };
                double angle = this.findAngle(vec1, vec2);
                if (angle < 90)
                {
                    this.colorPixels[(x0 + 0) + 640 * (y0 + 0)] = 0;
                    this.colorPixels[(x0 + 1) + 640 * (y0 + 0)] = 0;
                    this.colorPixels[(x0 + 2) + 640 * (y0 + 0)] = 255;
                }
            }
        }



    }
}
