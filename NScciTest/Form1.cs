using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using NScci;

namespace NScciTest
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Shown(object sender, EventArgs e)
        {
            NScci.NScci sim = new NScci.NScci();

            int n = sim.getInterfaceCount();
            if (n == 0)
            {
                sim.Dispose();
                return;
            }

            string s = sim.getcInterfaceNameFromInterfaceInfo(0);
            int c = sim.getiSoundChipCountFromInterfaceInfo(0);
            NSoundInterface nsif = sim.getInterface(0);
            bool f = nsif.isSupportLowLevelApi();
            n = nsif.getDelay();
            c = nsif.getSoundChipCount();
            NSoundChip nsc = nsif.getSoundChip(0);
            NSCCI_SOUND_CHIP_INFO nssci = nsc.getSoundChipInfo();
            string chipname = nssci.getcSoundChipName();
            long clock = nssci.getdClock();

            sim.Dispose();
        }
    }
}
