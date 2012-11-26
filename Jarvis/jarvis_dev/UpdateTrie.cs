using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Jarvis
{
    class UpdateTrie
    {
        public static void run(PhraseTrie lexicon)
        {
            String[] commands = {"run diablo iii"};
            Object[] actions = {new DiabloStart()};
            Boolean hasAdded = false;

            // Update the lexicon 
            for (int i = 0; i < commands.Count(); i++)
            {
                if (lexicon.addAction(commands[i], actions[i]))
                {
                    hasAdded = true;
                    FileOperations.writeText(commands[i], jarvis.comPath);
                }
            }

            // Write to the lexicon file
            FileOperations.ObjectToFile(lexicon, jarvis.lexPath);
        }
    }
}
