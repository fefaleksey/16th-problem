using System;
using System.Windows.Forms;

namespace Visualization
{
	internal class Program
	{
		[STAThread]
		public static void Main(string[] args)
		{
			Application.EnableVisualStyles();
			Application.SetCompatibleTextRenderingDefault(false);
			Application.Run(new EditorForm());
		}
	}
}