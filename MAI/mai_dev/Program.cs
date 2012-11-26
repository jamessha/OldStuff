using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Speech.Recognition;
using System.Speech.Synthesis;
using System.Text.RegularExpressions;

namespace MAI
{
    class mai
    {
        private SpeechRecognitionEngine recognizer;
        private Grammar dictationGrammar;
        private SpeechSynthesizer synthesizer;
        private PhraseTable responseTable;
        public static readonly String comPath = "data\\commands.txt";
        public static readonly String resPath = "data\\responseTable";
        private Random rand;

        // Regulating updating
        private static Boolean update = false;
        // Regulating debugging
        public static Boolean debug = false;
        public static Analytics analysis;

        // Initialization
        public mai()
        {
            recognizer = new SpeechRecognitionEngine();
            dictationGrammar = new DictationGrammar();
            recognizer.LoadGrammar(dictationGrammar);
            recognizer.SetInputToDefaultAudioDevice();
            synthesizer = new SpeechSynthesizer();
            rand = new Random();
            analysis = new Analytics();
            responseTable = (PhraseTable) FileOperations.FileToObject(resPath);
            if (responseTable == null)
            {
                responseTable = new PhraseTable();
            }   
        }

        // Voice synthesizer 
        public void synthesis(String to_say)
        {  
            synthesizer.SelectVoice("Microsoft Anna");
            synthesizer.Speak(to_say);
        }

        // Listens for commands
        private void command(String q)
        {
            String text = "";
            List<String> answer = new List<String>();
            
            while (true)
            {
                try
                {
                    //RecognitionResult result = recognizer.Recognize();
                    //Console.Out.WriteLine("Command Heard: " + result.Text);
                    //text = result.Text;
                    text = Console.ReadLine().ToLower();
                    if (endCommand(text))
                    {
                        break;
                    }
                    answer.Add(text);
                }
                catch (NullReferenceException e)
                {
                    Console.Out.WriteLine("Exception Encountered: {0}", e);
                }
            }
            this.parseResult(answer, q);
        }

        // Listens for phrases to start the recognition system
        private void recognition()
        {
            try
            {
                //RecognitionResult result = recognizer.Recognize();
                //Console.Out.WriteLine("Recognition Heard: " + result.Text);
                //String text = result.Text;
                String text = Console.ReadLine();
                if (beginCommand(text)){
                    String key = responseTable.getGraph().ElementAt(rand.Next(0, responseTable.getGraph().Count)).Key;

                    Console.Out.WriteLine("MAI: {0}", key);
                    //this.synthesis(pair.Key);
                    this.command(key);
                }
            }
            catch (NullReferenceException e)
            {
            }
        }

        // Determines if the result is valid and if so performs the desired action
        private void parseResult(List<String> text, String q)
        {
            // Taking care of the response
            List<PhraseTable.PhraseNode> returnedResponses = new List<PhraseTable.PhraseNode>();
            List<PhraseTable.PhraseNode> unrecognized = new List<PhraseTable.PhraseNode>();
            List<String> seen = new List<string>();

            foreach (String item in text)
            {
                PhraseTable.PhraseNode response = responseTable.getClosestResponse(q, item);

                if (response == null)
                {
                    unrecognized.Add(response);
                }
                else
                {
                    returnedResponses.Add(response);
                    seen.Add(item);
                }
            }



            // Prints all the information
            // NOTE: NEEDS SCORING SYSTEM
            // NOTE: Scoring system should account for things like "how specific were you" (ie number of each type)
            // Thoughts user got right
            if (!debug)
            {
                List<PhraseTable.PhraseNode> unseen = responseTable.getUnseen(q, returnedResponses);
                HashSet<String> reduceUnseen = new HashSet<String>();
                HashSet<String> reduceSeen = new HashSet<String>();
                Console.Out.WriteLine("");
                Console.Out.WriteLine("Thoughts you got:");
                if (seen.Count == 0)
                {
                    Console.Out.WriteLine("None");
                }
                for (int i = 0; i < seen.Count; i++)
                {
                    // Gotten thoughts should not be missed
                    reduceUnseen.Add(returnedResponses[i].getType());
                    // If thought had not been already detected
                    if (reduceSeen.Add(returnedResponses[i].getType()))
                    {
                        Console.Out.WriteLine(returnedResponses[i].getType());
                    }
                }
                // Thoughts user missed
                Console.Out.WriteLine("");
                Console.Out.WriteLine("Missed thoughts:");
                if (unseen.Count == 0)
                {
                    Console.Out.WriteLine("None");
                }
                foreach (PhraseTable.PhraseNode item in unseen)
                {
                    // If missed thought had not already been displayed
                    if (reduceUnseen.Add(item.getType()))
                    {
                        Console.Out.WriteLine(item.getType());
                    }
                }
                // Thoughts user got wrong
                Console.Out.WriteLine("");
                Console.Out.WriteLine("Rejected but possibly good thoughts:");
                if (unrecognized.Count == 0)
                {
                    Console.Out.WriteLine("None");
                }
                foreach (PhraseTable.PhraseNode item in unrecognized)
                {
                    Console.Out.WriteLine(item.getPhrase());
                }

                // Option for displaying debug data
                Console.Out.WriteLine("");
                Console.Out.WriteLine("Display Debug Statistics? y or n");
                if (Console.ReadLine().Equals("y"))
                {
                    debug = true;
                }
            }
            // Debugging, gets analytics
            if (debug)
            {
                Console.Out.WriteLine("");
                for (int i = 0; i < seen.Count; i++)
                {
                    Console.Out.WriteLine("You:                  {0}", seen[i]);
                    Console.Out.WriteLine("Closest Phrase Found: {0}", returnedResponses[i].getPhrase());
                    Console.Out.WriteLine("Closest Type Found:   {0}", returnedResponses[i].getType());
                }
                Console.Out.WriteLine("");
                Console.Out.WriteLine("Average closeness of answer: {0}", analysis.getAvg());
                Console.Out.WriteLine("SD of closeness of answer:   {0}", analysis.getSD());
            }
        }

        // Explicit command(s) to start the recognition system
        private Boolean beginCommand(String text)
        {
            text = text.ToLower();
            if (text.Equals("start"))
            {
                return true;
            }
            return false;
        }

        // Explicit command(s) to end the recognition system
        private Boolean endCommand(String text)
        {
            text = text.ToLower();
            if (text.Equals("stop"))
            {
                return true;
            }
            return false;
        }

        static void Main(string[] args)
        {
            // Booting up Jarvis
            Console.Out.WriteLine("Booting up MAI...");
            mai program = new mai();

            // Updating the graph and rebooting Jarvis to update his graph
            if (mai.update)
            {
                UpdateGraph.run(program.responseTable);
                program = new mai();
            }

            // Main loop
            Console.Out.WriteLine("Ready!");
            while (true)
            {
                program.recognition();
            }
            // speech_detector.recognizer.UnloadAllGrammars();

        }
    }
}
