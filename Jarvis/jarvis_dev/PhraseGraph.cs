using System;
using System.Collections.Generic;
using System.Collections;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Jarvis
{
    [Serializable]
    class PhraseGraph
    {
        // This is an overarching dictionary; Key: Phrase, Value: PhraseNode
        private Dictionary<String, PhraseNode> graph;
        private PhraseNode head;

        public PhraseGraph(String s)
        {
            head = new PhraseNode(s);
            graph = new Dictionary<string, PhraseNode>();
            graph.Add(s, head);
        }

        [Serializable]
        public class PhraseNode
        {
            // This is a dictionary specific to each PhraseNode; Key: Response, Value: next PhraseNode
            private List<PhraseNode> responses;
            private String phrase;
            private PhraseNode prev;
            private Random rand;

            public PhraseNode(String s)
            {
                responses = new List<PhraseNode>();
                this.phrase = s.ToLower();
                rand = new Random();
                prev = null;
            }

            public PhraseNode(String s, PhraseNode p)
            {
                responses = new List<PhraseNode>();
                this.phrase = s.ToLower();
                rand = new Random();
                prev = p;
            }

            // Adds a given PhraseNode 's' as the value to the required human response 'r'
            public void addResponse(PhraseNode s)
            {
                this.responses.Add(s);
                s.prev = this;
            }

            // Gets the appropriate PhraseNode given a human response 'r'
            // Random component of the list that corresponds to the response
            public PhraseNode getResponse(String r)
            {
                foreach (PhraseNode item in this.responses)
                {
                    if (item.getPhrase().Equals(r))
                    {
                        int randNum = rand.Next();
                        PhraseNode toReturn = null;
                        if (item.responses.Count != 0)
                        {
                            toReturn = item.responses[randNum % item.responses.Count];
                        }
                        return toReturn;
                    }
                }
                return null;
            }

            // Determines whether a given string is in the list of responses
            public Boolean contains(String r)
            {
                foreach (PhraseNode item in this.responses)
                {
                    if (item.getPhrase().Equals(r))
                    {
                        return true;
                    }
                }
                return false;
            }

            // Gets a random response
            public PhraseNode getRandom()
            {
                int randInt = rand.Next();
                if (this.responses.Count != 0)
                {
                    return this.responses[randInt % this.responses.Count];
                }
                return null;
            }

            // Finds the response with the most highest percentage of doublets
            public PhraseNode getClosestResponse(String s)
            {
                int maxCount = 0;
                PhraseNode toReturn = null;
                foreach (PhraseNode r in this.responses)
                {
                    int count = 0;
                    String rText = r.getPhrase();
                    String[] toComp1 = rText.Split(' ');
                    String[] toComp2 = s.Split(' ');
                    String[] toCompDoubles1 = new String[toComp1.Length];
                    String[] toCompDoubles2 = new String[toComp2.Length];
                    HashSet<String> set = new HashSet<String>();
                    for (int i = 1; i < toComp1.Length; i++)
                    {
                        toCompDoubles1[i-1] = toComp1[i-1] + toComp1[i];
                    }
                    for (int i = 1; i < toComp2.Length; i++)
                    {
                        toCompDoubles2[i-1] = toComp2[i-1] + toComp2[i];
                    }

                    foreach (String item in toCompDoubles1)
                    {
                        set.Add(item);
                    }
                    foreach (String item in toCompDoubles2)
                    {
                        if (!set.Add(item))
                        {
                            count++;
                        }
                    }

                    if (count > maxCount)
                    {
                        maxCount = count;
                        toReturn = r;
                    }
                }

                if (toReturn != null)
                {
                    return toReturn.getRandom();
                }
                return null;
            }

            // Returns the phrase contained in this PhraseNode
            public String getPhrase()
            {
                return this.phrase;
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

        // Adds a given phrase the PhraseNode it should be linked to; creates a new PhraseNode if one does not already exist
        public PhraseNode add(String s, PhraseNode addTo)
        {
            PhraseNode toAdd;
            graph.TryGetValue(s, out toAdd);
            if (toAdd == null)
            {
                toAdd = new PhraseNode(s);
            }
            graph[s] = toAdd;
            addTo.addResponse(toAdd);
            
            return toAdd;
        }

        // Returns the node of given phrase or null if it does not exist
        public PhraseNode get(String s)
        {
            PhraseNode toReturn;
            graph.TryGetValue(s, out toReturn);
            return toReturn;
        }

        public PhraseNode getHead()
        {
            return this.head;
        }

    }
}
