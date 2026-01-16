package UnSynk;

import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.io.File;
import java.util.HashMap;
import java.util.Map;
import javax.imageio.ImageIO;

public class bRend {

	private BufferedImage fontIm;
	private Map<Character, Glyph> glyphs = new HashMap<>();

	private static class Glyph {

		int x;
		int y;
		int width;
		int height;

		public Glyph(int x, int y, int w, int h) {
			this.x = x;
			this.y = y;
			this.width = w;
			this.height = h;
		}
	}

	public bRend(String path) throws Exception {
		fontIm = ImageIO.read(new File(path));

		glyphs.put(' ', new Glyph(0, 0, 8, 16));
		glyphs.put('!', new Glyph(0, 16, 8, 16));
		glyphs.put('"', new Glyph(0, 32, 8, 16));
		glyphs.put('#', new Glyph(0, 48, 8, 16));
		glyphs.put('$', new Glyph(0, 64, 8, 16));
		glyphs.put('%', new Glyph(0, 80, 8, 16));
		glyphs.put('&', new Glyph(0, 96, 8, 16));
		glyphs.put('(', new Glyph(0, 112, 8, 16));
		glyphs.put(')', new Glyph(0, 128, 8, 16));
		glyphs.put('*', new Glyph(0, 144, 8, 16));
		glyphs.put('+', new Glyph(0, 160, 8, 16));
		glyphs.put(',', new Glyph(0, 176, 8, 16));
		glyphs.put('-', new Glyph(0, 192, 8, 16));
		glyphs.put('.', new Glyph(0, 208, 8, 16));
		glyphs.put('/', new Glyph(0, 224, 8, 16));
		glyphs.put(':', new Glyph(0, 240, 8, 16));
		glyphs.put(';', new Glyph(0, 256, 8, 16));
		glyphs.put('<', new Glyph(0, 272, 8, 16));
		glyphs.put('=', new Glyph(0, 288, 8, 16));
		glyphs.put('>', new Glyph(0, 304, 8, 16));
		glyphs.put('?', new Glyph(0, 320, 8, 16));
		glyphs.put('@', new Glyph(0, 336, 8, 16));
		glyphs.put('[', new Glyph(0, 352, 8, 16));
		glyphs.put('\\', new Glyph(0, 368, 8, 16));
		glyphs.put(']', new Glyph(0, 384, 8, 16));
		glyphs.put('^', new Glyph(0, 400, 8, 16));
		glyphs.put('_', new Glyph(0, 416, 8, 16));
		glyphs.put('`', new Glyph(0, 432, 8, 16));
		glyphs.put('{', new Glyph(0, 448, 8, 16));
		glyphs.put('|', new Glyph(0, 464, 8, 16));
		glyphs.put('}', new Glyph(0, 480, 8, 16));
		glyphs.put('~', new Glyph(0, 496, 8, 16));
		glyphs.put('Е', new Glyph(0, 512, 8, 16));
		glyphs.put('Щ', new Glyph(0, 528, 8, 16));
		glyphs.put('Г', new Glyph(0, 544, 8, 16));
		glyphs.put('М', new Glyph(0, 560, 8, 16));
		glyphs.put('Р', new Glyph(0, 576, 8, 16));
		glyphs.put('О', new Glyph(0, 592, 8, 16));
		glyphs.put('Н', new Glyph(0, 608, 8, 16));
		glyphs.put('И', new Glyph(0, 624, 8, 16));
		glyphs.put('У', new Glyph(0, 640, 8, 16));
		glyphs.put('Э', new Glyph(0, 656, 8, 16));
		glyphs.put('Ы', new Glyph(0, 672, 8, 16));
		glyphs.put('А', new Glyph(0, 688, 8, 16));
		glyphs.put('Ъ', new Glyph(0, 704, 8, 16));
		glyphs.put('Ц', new Glyph(0, 720, 8, 16));
		glyphs.put('Ю', new Glyph(0, 736, 8, 16));
		glyphs.put('В', new Glyph(0, 752, 8, 16));
		glyphs.put('Б', new Glyph(0, 768, 8, 16));
		glyphs.put('Ф', new Glyph(0, 784, 8, 16));
		glyphs.put('П', new Glyph(0, 800, 8, 16));
		glyphs.put('Х', new Glyph(0, 816, 8, 16));
		glyphs.put('К', new Glyph(0, 832, 8, 16));
		glyphs.put('Ь', new Glyph(0, 848, 8, 16));
		glyphs.put('Я', new Glyph(0, 864, 8, 16));
		glyphs.put('Л', new Glyph(0, 880, 8, 16));
		glyphs.put('З', new Glyph(0, 896, 8, 16));
		glyphs.put('Д', new Glyph(0, 912, 8, 16));
		glyphs.put('С', new Glyph(0, 928, 8, 16));
		glyphs.put('Т', new Glyph(0, 944, 8, 16));
		glyphs.put('Й', new Glyph(0, 960, 8, 16));
		glyphs.put('е', new Glyph(0, 976, 8, 16));
		glyphs.put('щ', new Glyph(0, 992, 8, 16));
		glyphs.put('г', new Glyph(0, 1008, 8, 16));
		glyphs.put('м', new Glyph(0, 1024, 8, 16));
		glyphs.put('р', new Glyph(0, 1040, 8, 16));
		glyphs.put('о', new Glyph(0, 1056, 8, 16));
		glyphs.put('н', new Glyph(0, 1072, 8, 16));
		glyphs.put('и', new Glyph(0, 1088, 8, 16));
		glyphs.put('у', new Glyph(0, 1104, 8, 16));
		glyphs.put('э', new Glyph(0, 1120, 8, 16));
		glyphs.put('ы', new Glyph(0, 1136, 8, 16));
		glyphs.put('а', new Glyph(0, 1152, 8, 16));
		glyphs.put('ъ', new Glyph(0, 1168, 8, 16));
		glyphs.put('ц', new Glyph(0, 1184, 8, 16));
		glyphs.put('ю', new Glyph(0, 1200, 8, 16));
		glyphs.put('в', new Glyph(0, 1216, 8, 16));
		glyphs.put('б', new Glyph(0, 1232, 8, 16));
		glyphs.put('ф', new Glyph(0, 1248, 8, 16));
		glyphs.put('п', new Glyph(0, 1264, 8, 16));
		glyphs.put('х', new Glyph(0, 1280, 8, 16));
		glyphs.put('к', new Glyph(0, 1296, 8, 16));
		glyphs.put('ь', new Glyph(0, 1312, 8, 16));
		glyphs.put('я', new Glyph(0, 1328, 8, 16));
		glyphs.put('л', new Glyph(0, 1344, 8, 16));
		glyphs.put('з', new Glyph(0, 1360, 8, 16));
		glyphs.put('д', new Glyph(0, 1376, 8, 16));
		glyphs.put('с', new Glyph(0, 1392, 8, 16));
		glyphs.put('т', new Glyph(0, 1408, 8, 16));
		glyphs.put('й', new Glyph(0, 1424, 8, 16));
		glyphs.put('q', new Glyph(0, 1440, 8, 16));
		glyphs.put('w', new Glyph(0, 1456, 8, 16));
		glyphs.put('e', new Glyph(0, 1472, 8, 16));
		glyphs.put('r', new Glyph(0, 1488, 8, 16));
		glyphs.put('u', new Glyph(0, 1504, 8, 16));
		glyphs.put('i', new Glyph(0, 1520, 8, 16));
		glyphs.put('o', new Glyph(0, 1536, 8, 16));
		glyphs.put('p', new Glyph(0, 1552, 8, 16));
		glyphs.put('a', new Glyph(0, 1568, 8, 16));
		glyphs.put('s', new Glyph(0, 1584, 8, 16));
		glyphs.put('d', new Glyph(0, 1600, 8, 16));
		glyphs.put('f', new Glyph(0, 1616, 8, 16));
		glyphs.put('g', new Glyph(0, 1632, 8, 16));
		glyphs.put('h', new Glyph(0, 1648, 8, 16));
		glyphs.put('j', new Glyph(0, 1664, 8, 16));
		glyphs.put('k', new Glyph(0, 1680, 8, 16));
		glyphs.put('l', new Glyph(0, 1696, 8, 16));
		glyphs.put('z', new Glyph(0, 1712, 8, 16));
		glyphs.put('x', new Glyph(0, 1728, 8, 16));
		glyphs.put('c', new Glyph(0, 1744, 8, 16));
		glyphs.put('v', new Glyph(0, 1760, 8, 16));
		glyphs.put('b', new Glyph(0, 1776, 8, 16));
		glyphs.put('n', new Glyph(0, 1792, 8, 16));
		glyphs.put('m', new Glyph(0, 1808, 8, 16));
		glyphs.put('1', new Glyph(0, 1824, 8, 16));
		glyphs.put('2', new Glyph(0, 1840, 8, 16));
		glyphs.put('3', new Glyph(0, 1856, 8, 16));
		glyphs.put('4', new Glyph(0, 1872, 8, 16));
		// 罫線素材24, ブロック図形4
	}

	public int draw(Graphics2D g2d, String txt, int x, int y) {
		int crtX = x;

		for (char c : txt.toCharArray()) {
			Glyph g = glyphs.get(c);

			if (g != null) {
				g2d.drawImage(
					fontIm,
					crtX,
					y,
					crtX + g.width,
					y + g.height,
					g.x,
					g.y,
					g.x + g.width,
					g.y + g.height,
					null
				);
				crtX += g.width;
			}
		}

		return 0;
	}
}
