using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Jarvis
{
    [Serializable]
    class Introduction : ActionInterface
    {
        private readonly String history  = "I was built by James in the summer of o 12 as hack practice";

        public void run(jarvis ai)
        {
            ai.synthesis(history);
        }
    }
}
