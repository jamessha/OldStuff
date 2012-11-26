using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace Jarvis
{
    [Serializable]
    class Weather : ActionInterface
    {
        private String url = "http://www.google.com/ig/api?weather=94704";

        public void run(jarvis ai)
        {
            String toSay = "";
            Weather get = new Weather();
            List<String> weather = get.getWeather();
            foreach (String part in weather)
            {
                toSay += part;
                toSay += "         ";
            }

            ai.synthesis(toSay);
        }


        public List<String> getWeather()
        {
            List<String> toReturn = new List<String>();
            XmlTextReader reader = new XmlTextReader(url);
            String toAdd = "";
            int currentData = 3;

            while(reader.Read())
            {
                if (currentData == 0)
                {
                    break;
                }
                if(reader.NodeType.Equals(XmlNodeType.Element)){
                    if (reader.Name.Equals("condition"))
                    {
                        toAdd = "The current forcast is ";
                        while (reader.MoveToNextAttribute())
                        {
                            toAdd += reader.Value;
                        }
                        toReturn.Add(toAdd);
                        currentData -= 1;
                    }
                    if (reader.Name.Equals("low"))
                    {
                        toAdd = "Low of ";
                        while (reader.MoveToNextAttribute())
                        {
                            toAdd += reader.Value;
                        }
                        toReturn.Add(toAdd);
                        currentData -= 1;
                    }
                    if (reader.Name.Equals("high"))
                    {
                        toAdd = "High of ";
                        while (reader.MoveToNextAttribute())
                        {
                            toAdd += reader.Value;
                        }
                        toReturn.Add(toAdd);
                        currentData -= 1;
                    }
                    
                }
            }
            return toReturn;
        }
    }
}
