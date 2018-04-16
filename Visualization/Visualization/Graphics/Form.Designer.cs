using System.Drawing;
using System.Windows.Forms;

namespace Visualization
{
	internal partial class EditorForm
	{
		private const int Indenting = 100;

		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}

			base.Dispose(disposing);
		}

		private void InitializeComponent()
		{
			this.zedGraph = new ZedGraph.ZedGraphControl();
			this.menu = new MenuStrip();

			fileItem = new ToolStripMenuItem("File");
			runItem = new ToolStripMenuItem("Run");
			helpItem = new ToolStripMenuItem("Help");

			fileNewItem = new ToolStripMenuItem("New");
			fileExitItem = new ToolStripMenuItem("Exit");
			runRunItem = new ToolStripMenuItem("Run");
			helpRunExampleGraphItem = new ToolStripMenuItem("Run example graphic");
			helpRunExampleSyclesItem = new ToolStripMenuItem("Run example stability cycles");
			helpAboutItem = new ToolStripMenuItem("About");
			this.SuspendLayout();
			//
			// zedGraph
			//
			this.zedGraph.Dock = System.Windows.Forms.DockStyle.Fill;
			this.zedGraph.Location = new System.Drawing.Point(Indenting, Indenting);
			this.zedGraph.Name = "zedGraph";
			this.zedGraph.GraphPane.Title.Text = "Hello. Try click on Help -> Run example.";
			this.zedGraph.ScrollGrace = 0;
			this.zedGraph.ScrollMaxX = 0;
			this.zedGraph.ScrollMaxY = 0;
			this.zedGraph.ScrollMaxY2 = 0;
			this.zedGraph.ScrollMinX = 0;
			this.zedGraph.ScrollMinY = 0;
			this.zedGraph.ScrollMinY2 = 0;
			this.zedGraph.TabIndex = 0;
			//
			// MenuStrip
			//
			fileNewItem.Click += FileNewItem_Click;
			fileExitItem.Click += FileExitItem_Click;
			runRunItem.Click += RunRunItem_Click;
			helpRunExampleGraphItem.Click += HelpRunExampleGraphItem_Click;
			helpRunExampleSyclesItem.Click += HelpRunExampleSyclesItem_Click;
			helpAboutItem.Click += HelpAboutItem_Click;

			this.menu.Items.Add(fileItem);
			this.menu.Items.Add(runItem);
			this.menu.Items.Add(helpItem);

			this.fileItem.DropDownItems.Add(fileNewItem);
			this.fileItem.DropDownItems.Add(fileExitItem);

			this.runItem.DropDownItems.Add(runRunItem);

			this.helpItem.DropDownItems.Add(helpRunExampleGraphItem);
			this.helpItem.DropDownItems.Add(helpRunExampleSyclesItem);
			this.helpItem.DropDownItems.Add(helpAboutItem);
			// 
			// EditorForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.BackColor = System.Drawing.Color.White;
			this.DoubleBuffered = true;
			this.Name = "EditorForm";
			this.Text = "Visualization";
			this.Controls.Add(this.zedGraph);
			this.Controls.Add(this.menu);
			this.WindowState = FormWindowState.Maximized;
			this.ResumeLayout(false);
		}

		private ZedGraph.ZedGraphControl zedGraph;
		private MenuStrip menu;

		private ToolStripMenuItem fileItem;
		private ToolStripMenuItem runItem;
		private ToolStripMenuItem helpItem;

		private ToolStripMenuItem fileNewItem;
		private ToolStripMenuItem fileExitItem;

		private ToolStripMenuItem runRunItem;

		private ToolStripMenuItem helpRunExampleGraphItem;
		private ToolStripMenuItem helpRunExampleSyclesItem;
		private ToolStripMenuItem helpAboutItem;
	}
}