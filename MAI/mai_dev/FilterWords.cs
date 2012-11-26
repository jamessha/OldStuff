using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Text.RegularExpressions;

namespace MAI
{
    class FilterWords
    {
        private static readonly String[] units = {"meter", "kilometer", "gram", "kilogram", "second", "minute", 
                                                     "hour", "day", "week", "month", "year", "inch", "feet", "foot", 
                                                     "yard", "mile", "ounc", "pound", "ton", "cup", "gallon", 
                                                     "liter", "hundred", "thousand", "million", "billion", "trillion"};

        public static String filter(String s)
        {
            String toCombine;
            int n;
            bool isNum = int.TryParse(s, out n);
            // Get rid of numbers
            if (isNum)
            {
                toCombine = "#";
            }
            else
            {
                // Get rid of punctuations
                toCombine = Regex.Replace(s, @"\p{P}", "");
                // Get rid of articles 
                if (toCombine.IndexOfAny("NhVtiAvro".ToCharArray()) == -1)
                {
                    toCombine = "";
                }
                // Get rid of plurals
                if (toCombine.Length >= 2 && toCombine.Substring(toCombine.Length - 2, 2).Equals("es"))
                {
                    toCombine = toCombine.Substring(0, toCombine.Length - 2);
                }
                else if (toCombine.Length >= 1 && toCombine.Substring(toCombine.Length - 1, 1).Equals("s"))
                {
                    toCombine = toCombine.Substring(0, toCombine.Length - 1);
                }
                // Get rid of units
                if (units.Contains(toCombine))
                {
                    toCombine = "unit";
                }
            }

            return toCombine;
        }
    }
}
