using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Jarvis
{
    [Serializable]
    class GestureStart : ActionInterface
    {
        public void run(jarvis ai)
        {
            try
            {
                System.Diagnostics.Process.Start("E:\\Dropbox\\Projects\\AI\\Kinect\\Cursor\\bin\\Debug\\SkeletonBasics-WPF.exe");
            }
            catch (Exception _Exception)
            {
                Console.Out.WriteLine("Error Encountered: {0}", _Exception);
            }
        }
    }
}
