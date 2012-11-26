using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Diagnostics;
using System.IO;
using System.Windows;
using System.Windows.Media;

namespace Cursor3
{
    class Gesture
    {
        // The parent
        private Cursor3.MainWindow parent;

        // Keypresses, all actions based off of SendKeys
        [DllImport("user32.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        public static extern void mouse_event(uint dwFlags, uint dx, uint dy, int cButtons, int dwExtraInfo);
        private const int MOUSEEVENTF_LEFTDOWN = 0x02; // left button down
        private const int MOUSEEVENTF_LEFTUP = 0x04; // left button up
        private const int MOUSEEVENTF_RIGHTDOWN = 0x08; // right button down
        private const int MOUSEEVENTF_RIGHTUP = 0x10; // right button up
        private const int MIDDLEDOWN = 0x20; // middle button down
        private const int MIDDLEUP = 0x40; // middle button up 
        private const int WHEEL = 0x0800; // wheel button rolled 

        [DllImport("user32.dll", SetLastError = true)]
        public static extern void keybd_event(byte bVk, byte bScan, int dwFlags, int dwExtraInfo);
        private const int KEYEVENTF_EXTENDEDKEY = 0x0001; //Key down flag
        private const int KEYEVENTF_KEYUP = 0x0002; //Key up flag
        private const int VK_RCONTROL = 0xA3; //Right Control key code

        // Location Control
        private int lastCursorX = 0;
        private int lastCursorY = 0;
        private int lastHandX = 0;
        private int lastHandY = 0;

        // Cursor Control
        Cursor Cursor;

        // Action Control (based off of frame counters)
        private int fiveFingerFrameCount = 0;
        private int fourFingerFrameCount = 0;
        private int threeFingerFrameCount = 0;
        private int twoFingerFrameCount = 0;
        bool holding = false;


        public Gesture(Cursor3.MainWindow parent)
        {
            this.parent = parent;
            Cursor = new Cursor(Cursor.Current.Handle);
            System.Drawing.Point currPoint = Cursor.Position;
            this.lastCursorX = currPoint.X;
            this.lastCursorY = currPoint.Y;
        }

        // Handles movement of the hand
        public void handMovement(int x, int y, int numFingers)
        {
            int deltaX = x - lastHandX;
            int deltaY = y - lastHandY;
            // Move the cursor normally
            if (numFingers != 2 && numFingers != 3)
            {
                Cursor = new Cursor(Cursor.Current.Handle);
                Cursor.Position = new System.Drawing.Point(lastCursorX + deltaX, lastCursorY + deltaY);
                this.twoFingerFrameCount = 0;
                this.threeFingerFrameCount = 0;
            }
            // Scroll in the case of two fingers
            else if (numFingers == 2)
            {
                this.twoFingerFrameCount++;
                if (this.twoFingerFrameCount >= 3 && deltaY >= 5)
                {
                    mouse_event(WHEEL, (uint)Cursor.Position.X, (uint) Cursor.Position.Y, 300, 0);
                } 
                else if (this.twoFingerFrameCount >= 3 && deltaY<= -5)
                {
                    mouse_event(WHEEL, (uint) Cursor.Position.X, (uint) Cursor.Position.Y, -300, 0);
                }
            }
            // Zoom in the case of three fingers
            else if (numFingers == 3)
            {
                this.threeFingerFrameCount++;
                if (this.threeFingerFrameCount >= 3 && deltaY >= 5 && deltaY <= 20)
                {
                    keybd_event(VK_RCONTROL, 0, KEYEVENTF_EXTENDEDKEY, 0);
                    mouse_event(WHEEL, (uint)Cursor.Position.X, (uint)Cursor.Position.Y, 300, 0);
                    keybd_event(VK_RCONTROL, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
                }
                else if (this.threeFingerFrameCount >= 3 && deltaY <= -5 && deltaY >= -20)
                {
                    keybd_event(VK_RCONTROL, 0, KEYEVENTF_EXTENDEDKEY, 0);
                    mouse_event(WHEEL, (uint)Cursor.Position.X, (uint)Cursor.Position.Y, -300, 0);
                    keybd_event(VK_RCONTROL, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
                }
            }
            lastCursorX = lastCursorX + deltaX;
            lastCursorY = lastCursorY + deltaY;
            lastHandX = x;
            lastHandY = y;


            // Text, need to change to string formatting for cleanliness later
            if (this.twoFingerFrameCount >= 3)
            {
                parent.setText("Ready to register scroll: TRUE\n");
            }
            else
            {
                parent.setText("Ready to register scroll: FALSE\n");
            }
            if (this.threeFingerFrameCount >= 3)
            {
                parent.setText("Ready to register zoom: TRUE\n");
            }
            else
            {
                parent.setText("Ready to register zoom: FALSE\n");
            }
        }

        // Abstraction for setting the hand location
        public void setHand(int x, int y)
        {
            lastHandX = x;
            lastHandY = y;
        }

        // Handles the clicking of the mouse 
        public void clickMouse(int numFinger)
        {
            // Always check to release from a hold
            if (this.holding && numFinger >= 3)
            {
                mouse_event(MOUSEEVENTF_LEFTUP, (uint)Cursor.Position.X, (uint)Cursor.Position.Y, 0, 0);
                this.holding = false;
            }
            // Five fingers is the baseline position for launching actions
            if (numFinger == 5)
            {
                this.fiveFingerFrameCount++;
                this.fourFingerFrameCount = 0;
            }
            // One finger down is single click position, must be launched after holding 5 fingers for a set period to reduce false positives
            else if (numFinger == 4 && this.fiveFingerFrameCount >= 10)
            {
                this.fourFingerFrameCount++;
                // Must have held position for set period to reduce false positives, reset after launching action
                if (this.fourFingerFrameCount >= 5)
                {
                    mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, (uint) Cursor.Position.X, (uint) Cursor.Position.Y, 0, 0);
                    this.fourFingerFrameCount = 0;
                    this.fiveFingerFrameCount = 0;
                }
            }
            // Initiate a hold by jumping from 5 to 0 fingers, uses 5 finger (x, y) to prevent jumping when closing hand
            else if (numFinger == 0 && this.fiveFingerFrameCount >= 10)
            {
                mouse_event(MOUSEEVENTF_LEFTDOWN, (uint) this.lastCursorX, (uint) this.lastCursorY, 0, 0);
                this.holding = true;
            }
            // Random flickers reset the baseline count
            else
            {
                this.fiveFingerFrameCount = 0;
            }

            if (this.fiveFingerFrameCount >= 10)
            {
                parent.setText("Ready to register click: TRUE\n");
            }
            else
            {
                parent.setText("Ready to register click: FALSE\n");
            }
        }

        // Resets the counters
        public void reset()
        {
            this.twoFingerFrameCount = 0;
            this.threeFingerFrameCount = 0;
            this.fourFingerFrameCount = 0;
            this.fiveFingerFrameCount = 0;
        }
    }
}
