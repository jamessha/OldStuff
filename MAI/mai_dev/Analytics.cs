using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MAI
{
    [Serializable]
    class Analytics
    {
        private double avg;
        private double sd;

        private List<int> distList;

        public Analytics()
        {
            this.avg = 0;
            this.sd = 0;
            this.distList = new List<int>();
        }

        public void addData(int n)
        {
            this.distList.Add(n);
            avg = (avg * (this.distList.Count - 1) + n) / (this.distList.Count);
            sd = Math.Sqrt(((sd * sd) * (this.distList.Count - 1) + ((avg - n) * (avg - n))) / this.distList.Count);
        }

        public double getAvg()
        {
            return this.avg;
        }

        public double getSD()
        {
            return this.sd;
        }
    }
}
