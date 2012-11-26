using System;
using System.Collections.Generic;
using System.Collections;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Text.RegularExpressions;

namespace MAI
{
    [Serializable]
    class PhraseTable
    {
        private PartOfSpeech grammarDic;

        // This is an overarching dictionary; Key: Phrase, Value: PhraseNode
        private Dictionary<String, PhraseNode> table;

        public PhraseTable()
        {
            table = new Dictionary<string, PhraseNode>();
            grammarDic = new PartOfSpeech();
        }

        [Serializable]
        public class PhraseNode
        {
            // This is a dictionary specific to each PhraseNode; Key: Response, Value: next PhraseNode
            private String phrase;
            private String type;
            private PhraseNode prev;
            private PhraseNode next;

            public PhraseNode(String p, String t)
            {
                this.phrase = p.ToLower();
                this.type = t;
                prev = null;
                next = null;
            }

            // Adds a given PhraseNode 's' as the value to the required human response 'r'
            public void add(PhraseNode s)
            {
                this.next = s;
                s.setPrev(this);
            }

            // Returns the phrase contained in this PhraseNode
            public String getPhrase()
            {
                int n;
                bool isNum = int.TryParse(this.phrase, out n);
                if (isNum)
                {
                    return "#";
                }
                return this.phrase;
            }

            public String getType()
            {
                return this.type;
            }

            public PhraseNode getNext()
            {
                return this.next;
            }

            public override int GetHashCode()
            {
                return this.phrase.GetHashCode();
            }

            public void setPrev(PhraseNode x)
            {
                this.prev = x;
            }

            public PhraseNode getPrev()
            {
                return this.prev;
            }

        }

        // Adds a given phrase to the PhraseNode it should be linked to
        public PhraseNode add(String key, String value1, String value2)
        {
            PhraseNode toAdd = new PhraseNode(value1, value2);
            table[key] = null;
            table[key] = toAdd;
            return toAdd;
        }

        // Returns the node of given phrase or null if it does not exist
        public PhraseNode get(String s)
        {
            PhraseNode toReturn;
            table.TryGetValue(s, out toReturn);
            return toReturn;
        }

        // Returns all unseen answers
        public List<PhraseNode> getUnseen(String key, List<PhraseNode> seen)
        {
            List<PhraseNode> unseen = new List<PhraseNode>();
            PhraseNode curr = table[key];

            while (curr != null)
            {
                if (!seen.Contains(curr))
                {
                    unseen.Add(curr);
                }
                curr = curr.getNext();
            }
            return unseen;
        }

        // Returns the graph
        public Dictionary<String, PhraseNode> getGraph()
        {
            return this.table;
        }

        // Finds the response with the most highest number of doublets
        public PhraseNode getClosestResponse(String q, String s)
        {
            int maxCount = -1;
            PhraseNode toReturn = null;
            PhraseNode r = this.table[q];
            while (r.getNext() != null)
            {
                int count = 0;
                String rText = r.getPhrase();
                String[] toComp1 = rText.Split(' ');
                String[] toComp2 = s.Split(' ');
                List<String> toCompDoubles1 = new List<String>();
                List<String> toCompDoubles2 = new List<String>();
                HashSet<String> set = new HashSet<String>();
                // Here we will isolate punctuations and split words up into doublets 
                for (int i = 2; i < toComp1.Length; i++)
                {
                    String toCombine1 = FilterWords.filter(toComp1[i - 2]);
                    String toCombine2 = FilterWords.filter(toComp1[i - 1]);
                    String toCombine3 = FilterWords.filter(toComp1[i]);
                    if (!(toCombine1 + toCombine2).Equals(""))
                    {
                        set.Add(toCombine1 + toCombine2);
                    }
                    if (!(toCombine1 + toCombine3).Equals(""))
                    {
                        set.Add(toCombine1 + toCombine3);
                    }
                    if (!(toCombine2 + toCombine3).Equals(""))
                    {
                        set.Add(toCombine2 + toCombine3);
                    }
                }
                for (int i = 2; i < toComp2.Length; i++)
                {
                    String toCombine1 = FilterWords.filter(toComp2[i - 2]);
                    String toCombine2 = FilterWords.filter(toComp2[i - 1]);
                    String toCombine3 = FilterWords.filter(toComp2[i]);
                    if (!(toCombine1 + toCombine2).Equals(""))
                    {
                        if (!(toCombine1 + toCombine2).Equals(""))
                        {
                            count++;
                        }
                    }
                    if (!(toCombine1 + toCombine3).Equals(""))
                    {
                        if (!set.Add(toCombine1 + toCombine3))
                        {
                            count++;
                        }
                    }
                    if (!(toCombine2 + toCombine3).Equals(""))
                    {
                        if (!set.Add(toCombine2 + toCombine3))
                        {
                            count++;
                        }
                    }
                }

                if (count > maxCount)
                {
                    maxCount = count;
                    toReturn = r;
                }

                r = r.getNext();
            }

            // Analytics
            mai.analysis.addData(maxCount);

            if (maxCount == 0)
            {
                return null;
            }

            // Adds the current phrase in question to the list if the answer is deemed close enough 
            if (maxCount > 99)
            {
                r.add(new PhraseNode(s, toReturn.getType()));
            }
            return toReturn;
        }

        public void toString()
        {
            foreach (KeyValuePair<String, PhraseNode> pair in table)
            {
                String q = pair.Key;
                Console.Out.WriteLine("");
                Console.Out.WriteLine(q);
                PhraseNode curr = table[q];
                while (curr.getNext() != null)
                {
                    Console.Out.WriteLine("Phrase: {0}", curr.getPhrase());
                    Console.Out.WriteLine("Type:   {0}", curr.getType());
                    curr = curr.getNext();
                }
            }
        }

    }
}
