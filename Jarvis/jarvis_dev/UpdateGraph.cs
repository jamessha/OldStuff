using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Text.RegularExpressions;

namespace Jarvis
{
    class UpdateGraph
    {
        private static readonly string path = "data\\convos.txt";

        public static void run(PhraseGraph g)
        {
            PhraseGraph.PhraseNode currNode;

            String text = FileOperations.readText(path);
            String[] textConvos = Regex.Split(text, "\r\n\r\n");

            foreach (String convo in textConvos)
            {
                currNode = g.getHead();

                String[] textLines = Regex.Split(convo, "\r\n");
                foreach (String line in textLines)
                {
                    currNode = g.add(line, currNode);
                }
            }

            // Write to the lexicon file
            FileOperations.ObjectToFile(g, jarvis.resPath);
        }

    }
}
