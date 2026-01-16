/* Бинарйзмер */
import java.awt.*;
import javax.swing.*;

import UnSynk.bRend;

public class Бинарйзмер extends JPanel
{
	private bRend rend;

	@Override
	protected void paintComponent(Graphics g)
	{
		super.paintComponent(g);
		Graphics2D g2d = (Graphics2D)g;

		setBackground(Color.BLACK);

		try
		{
			rend = new bRend("Хамор.bmp");

			rend.draw(g2d, "eooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooor44", 0, 0);
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
	}

	public static void main(String[] args)
	{
		JFrame frame = new JFrame("Бинарйзмер");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(640, 400);

		frame.add(new Бинарйзмер());

		frame.setLocationRelativeTo(null);
		frame.setVisible(true);
	}
}
