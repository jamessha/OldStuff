using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections;

namespace Jarvis
{
    [Serializable]
    class PhraseTrie
    {
        /* 
         * Creates a trie of phrases in that each node is a word
        */

        private TrieNode lexicon;

        public PhraseTrie()
        {
            lexicon = new TrieNode();
        }

        [Serializable]
        private class TrieNode
        {
            private List<TrieNode> childWords;
            private String item;
            public Boolean anotherEnd;
            public Boolean end;
            public Object action;

            public TrieNode()
            {
            }

            public TrieNode(String first)
            {
                item = first;
                childWords = new List<TrieNode>();
                anotherEnd = false;
                end = true;
            }

            // Adds a child to the current node and returns it
            public TrieNode add(TrieNode child)
            {
                if (!anotherEnd)
                {
                    end = false;
                }
                for (int i = 0; i < childWords.Count; i++)
                {
                    if (childWords[i].item.Equals(child.item))
                    {
                        return childWords[i];
                    }
                }
                childWords.Add(child);
                return child;
            }

            // Gets the node of a particular word should it be a child of the current node
            public TrieNode get(String s)
            {
                for (int i = 0; i < childWords.Count; i++)
                {
                    if (childWords[i].item.Equals(s))
                    {
                        return childWords[i];
                    }
                }
                return null;
            }

            // Determines if a word is a child of the current node
            public Boolean hasWord(String s)
            {
                for (int i = 0; i < childWords.Count; i++)
                {
                    if (childWords[i].item.Equals(s))
                    {
                        return true;
                    }
                }
                return false;
            }

            public override Boolean Equals(Object c)
            {
                return this.item == ((TrieNode) c).item;
            }
        }

        // Adds a phrase and corresponding action into the trie
        // Returns true if the phrase is not already in otherwise returns false
        public Boolean addAction(String input, Object a)
        {
            int count = 0;
            String[] inputPieces = input.Split(' ');
            TrieNode prev = lexicon;
            foreach (String piece in inputPieces)
            {
                String toAdd = piece.ToLower();
                TrieNode nodeToAdd = new TrieNode(toAdd);
                TrieNode curr = prev.add(nodeToAdd);
                if (nodeToAdd != curr)
                {
                    count += 1;
                }
                prev = curr;
            }

            prev.anotherEnd = true;
            prev.action = a;

            if (count == inputPieces.Count())
            {
                return false;
            }
            return true;
        }

        // Checks to see if a phrase exists returning the action if so an null if not
        public Object getAction(String s)
        {
            String[] inputPieces = s.Split(' ');
            TrieNode currWords = lexicon;
            foreach (String piece in inputPieces)
            {
                String toFind = piece.ToLower();
                if (currWords.hasWord(toFind))
                {
                    currWords = currWords.get(toFind);
                }
                else
                {
                    return null;
                }
            }
            if (currWords.end)
            {
                return currWords.action;
            }
            return null;
        }

    }
}
