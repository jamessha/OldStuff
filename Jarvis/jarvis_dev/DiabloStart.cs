using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Jarvis
{
    [Serializable]
    class DiabloStart : ActionInterface
    {
        public void run(jarvis ai)
        {
            try
            {
                System.Diagnostics.Process.Start("C:\\Program Files (x86)\\Diablo III\\Diablo III Launcher.exe");
            }
            catch (Exception _Exception)
            {
                Console.Out.WriteLine("Error Encountered: {0}", _Exception);
            }
        }
    }
}
