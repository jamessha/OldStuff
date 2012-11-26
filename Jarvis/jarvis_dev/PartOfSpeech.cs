using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Text.RegularExpressions;

namespace Jarvis
{
    class PartOfSpeech
    {
        private Dictionary<String, String> pos;
        private String path = "E:\\Dropbox\\Projects\\AI\\Jarvis\\data\\pos\\part-of-speech.txt";

        public PartOfSpeech()
        {
            pos = new Dictionary<string,string>();
            String[] lines = FileOperations.readTextLines(path);
            foreach (String line in lines)
            {
                String[] lineParts = Regex.Split(line, "\t");
                String word = lineParts[0].ToLower();
                String type = lineParts[1];
                pos[word] = type;
            }
        }

        public String getType(String word)
        {
            try
            {
                word = word.ToLower();
                return pos[word];
            }
            catch (Exception e)
            {
                Console.Out.WriteLine("Exception: Word Not Found");
            }
            return null;
        }
    }
}
