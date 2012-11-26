using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Jarvis
{
    class CloseApp
    {
        private Process[] processes;

        public void getApp(jarvis ai)
        {
            String text = "";
            while (!endCommand(text))
            {
                try
                {
                    RecognitionResult result = recognizer.Recognize();
                    Console.Out.WriteLine("Command Heard: " + result.Text);
                    text = result.Text;
                    this.parseResult(text);
                }
                catch (NullReferenceException e)
                {
                }
            }
        }

    }
}
