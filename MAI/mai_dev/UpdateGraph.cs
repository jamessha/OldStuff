using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Text.RegularExpressions;

namespace MAI
{
    class UpdateGraph
    {
        private static readonly string path = "data\\questions\\size_of_bubble_gum_market_us.txt";

        public static void run(PhraseTable g)
        {
            Console.Out.WriteLine("Updating MAI...");
            PhraseTable.PhraseNode currNode;

            String text = FileOperations.readText(path);
            String[] textConvos = Regex.Split(text, "\r\n\r\n\r\n");

            String question = textConvos[0];
            String answers = textConvos[1];
            String[] answersLines = Regex.Split(answers, "\r\n\r\n");

            currNode = g.add(question, Regex.Split(answersLines[0], "\r\n")[0], Regex.Split(answersLines[0], "\r\n")[1]);

            for (int i = 1; i < answersLines.Length; i++)
            {
                String[] s = Regex.Split(answersLines[i], "\r\n");
                

                PhraseTable.PhraseNode toAdd = new PhraseTable.PhraseNode(s[0], s[1]);
                currNode.add(toAdd);
                currNode = toAdd;

            }

            // Write to the graph file
            FileOperations.ObjectToFile(g, mai.resPath);
            Console.Out.WriteLine("Done!");
        }

    }
}
