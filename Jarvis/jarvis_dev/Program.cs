using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Speech.Recognition;
using System.Speech.Synthesis;
using System.Text.RegularExpressions;

namespace Jarvis
{
    class jarvis
    {
        private SpeechRecognitionEngine recognizer;
        private Grammar dictationGrammar;
        private SpeechSynthesizer synthesizer;
        private PhraseTrie lexicon;
        private PhraseGraph responseGraph;
        private PhraseGraph.PhraseNode responseNode;
        public static readonly String lexPath = "data\\lexicon";
        public static readonly String comPath = "data\\commands.txt";
        public static readonly String resPath = "data\\responseGraph";

        // Initialization
        public jarvis()
        {
            recognizer = new SpeechRecognitionEngine();
            dictationGrammar = new DictationGrammar();
            recognizer.LoadGrammar(dictationGrammar);
            recognizer.SetInputToDefaultAudioDevice();
            synthesizer = new SpeechSynthesizer();
            lexicon = (PhraseTrie) FileOperations.FileToObject(lexPath);
            if (lexicon == null)
            {
                lexicon = new PhraseTrie();
            }
            responseGraph = (PhraseGraph) FileOperations.FileToObject(resPath);
            if (responseGraph == null)
            {
                responseGraph = new PhraseGraph("");
            }
            responseNode = responseGraph.getHead();
            
        }

        // Voice synthesizer 
        public void synthesis(String to_say)
        {  
            synthesizer.SelectVoice("Microsoft Anna");
            synthesizer.Speak(to_say);
        }

        // Listens for commands
        private void command()
        {
            String text = "";
            while (true)
            {
                try
                {
                    RecognitionResult result = recognizer.Recognize();
                    Console.Out.WriteLine("Command Heard: " + result.Text);
                    text = result.Text;
                    //text = Console.ReadLine();
                    if (endCommand(text))
                    {
                        break;
                    }
                    this.parseResult(text);
                }
                catch (NullReferenceException e)
                {
                }
            }

            FileOperations.ObjectToFile(responseGraph, jarvis.resPath);
            this.synthesis("Ended command loop");
        }

        // Listens for phrases to start the recognition system
        private void recognition()
        {
            try
            {
                RecognitionResult result = recognizer.Recognize();
                Console.Out.WriteLine("Recognition Heard: " + result.Text);
                String text = result.Text;
                //String text = Console.ReadLine();
                if (beginCommand(text))
                {
                    this.responseNode = responseGraph.getHead();
                    this.synthesis("I am listening");
                    this.command();
                }
            }
            catch (NullReferenceException e)
            {
            }
        }

        // Determines if the result is valid and if so performs the desired action
        private void parseResult(String text)
        {
            // Taking care of any action required
            ActionInterface action = (ActionInterface)lexicon.getAction(text);
            if (action != null)
            {
                action.run(this);
            }
            else
            {
                Console.Out.WriteLine("No Action Found");
            }

            // Taking care of the response
            PhraseGraph.PhraseNode response = responseNode.getClosestResponse(text);
            if (response != null)
            {
                responseGraph.add(text, responseNode);
                String responseText = response.getPhrase();
                Console.Out.WriteLine("Jarvis: {0}", responseText);
                this.synthesis(responseText);
                responseNode = response;
            }
            else
            {
                response = responseGraph.add(text, responseNode);
                String responseText = response.getPhrase();
                //Console.Out.WriteLine("Adding: {0}", responseText);
                this.synthesis(responseText);
                responseNode = response;
            }
        }

        // Explicit command(s) to start the recognition system
        private Boolean beginCommand(String text)
        {
            text = text.ToLower();
            // Microsoft voice recognition is terrible
            if (text.Equals("hey jarvis") || text.Equals("in terms") || text.Equals("the terms") || text.Equals("the firms") || text.Equals("the firm is") || text.Equals("the times"))
            {
                return true;
            }
            return false;
        }

        // Explicit command(s) to end the recognition system
        private Boolean endCommand(String text)
        {
            text = text.ToLower();
            if (text.Equals("that's all for now jarvis"))
            {
                return true;
            }
            return false;
        }

        static void Main(string[] args)
        {
            // Booting up Jarvis
            jarvis speech_detector = new jarvis();

            // Updating the lexicon and rebooting Jarvis to update his lexicon
            UpdateTrie.run(speech_detector.lexicon);
            speech_detector = new jarvis();

            // Updating the graph and rebooting Jarvis to update his graph
            //UpdateGraph.run(speech_detector.responseGraph);
            //speech_detector = new jarvis();

            // Main loop
            while (true)
            {
                speech_detector.recognition();
            }
            // speech_detector.recognizer.UnloadAllGrammars();

        }
    }
}
