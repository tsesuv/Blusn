import java.awt.*;
import java.io.*;
import javax.swing.*;

public class sbv extends JFrame
{
	private int width = 1304;
	private int height = 24;
	private byte[] data;

	private DrawPanel drawPanel;

	public sbv()
	{
		super("1bit Font Viewer");

		// 初期パネル
		drawPanel = new DrawPanel();
		add(new JScrollPane(drawPanel), BorderLayout.CENTER);

		// メニューバー
		JMenuBar menuBar = new JMenuBar();
		JMenu fileMenu = new JMenu("File");
		JMenuItem openItem = new JMenuItem("Open...");
		openItem.addActionListener(e -> loadFile());
		fileMenu.add(openItem);

		JMenu sizeMenu = new JMenu("Size");
		JMenuItem setSizeItem = new JMenuItem("Set Width/Height...");
		setSizeItem.addActionListener(e -> setSizeDialog());
		sizeMenu.add(setSizeItem);

		menuBar.add(fileMenu);
		menuBar.add(sizeMenu);
		setJMenuBar(menuBar);

		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setSize(800, 600);
		setLocationRelativeTo(null);
		setVisible(true);
	}

	private void loadFile()
	{
		JFileChooser chooser = new JFileChooser();
		if(chooser.showOpenDialog(this) == JFileChooser.APPROVE_OPTION)
		{
			try
			{
				File file = chooser.getSelectedFile();
				FileInputStream fis = new FileInputStream(file);
				data = fis.readAllBytes();
				fis.close();
				drawPanel.repaint();
			}
			catch(IOException ex)
			{
				JOptionPane.showMessageDialog(this, "File read error: " + ex.getMessage());
			}
		}
	}

	private void setSizeDialog()
	{
		JTextField wField = new JTextField(String.valueOf(width));
		JTextField hField = new JTextField(String.valueOf(height));
		JPanel panel = new JPanel(new GridLayout(2, 2));
		panel.add(new JLabel("Width:"));
		panel.add(wField);
		panel.add(new JLabel("Height:"));
		panel.add(hField);

		int result = JOptionPane.showConfirmDialog(this, panel, "Set Image Size", JOptionPane.OK_CANCEL_OPTION);
		if(result == JOptionPane.OK_OPTION)
		{
			try
			{
				width = Integer.parseInt(wField.getText());
				height = Integer.parseInt(hField.getText());
				drawPanel.repaint();
			}
			catch(NumberFormatException ex)
			{
				JOptionPane.showMessageDialog(this, "Invalid number format.");
			}
		}
	}

	private class DrawPanel extends JPanel
	{
		@Override
		public Dimension getPreferredSize()
		{
			return new Dimension(width, height);
		}

		@Override
		protected void paintComponent(Graphics g)
		{
			super.paintComponent(g);
			if(data == null) return;

			int bitIndex = 0;
			for(int y = 0; y < height; y++)
			{
				for(int x = 0; x < width; x++)
				{
					int byteIndex = bitIndex / 8;
					int bitPos = 7 - (bitIndex % 8);

					if(byteIndex < data.length)
					{
						int value = (data[byteIndex] >> bitPos) & 1;
						g.setColor(value == 1 ? Color.WHITE : Color.BLACK);
						g.fillRect(x, y, 1, 1);
					}
					bitIndex++;
				}
			}
		}
	}

	public static void main(String[] args)
	{
		SwingUtilities.invokeLater(sbv::new);
	}
}
