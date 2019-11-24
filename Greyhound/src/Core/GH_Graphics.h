#pragma once

#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>
#include FT_FREETYPE_H 

class GH_Graphics
{
public:
	GH_Graphics(int w, int h) 
	{ 
		this->width = w; 
		this->height = h; 
		this->shapeShader = new Shader("res\\shaders\\shape.vs", "res\\shaders\\shape.fs");
		this->textShader = new Shader("res\\shaders\\text.vs", "res\\shaders\\text.fs");

		this->face = NULL;
		this->ft = NULL;
		
	}
	~GH_Graphics() 
	{
		std::map<const char*, font_data>::iterator it;
		for (it = this->fonts.begin(); it != this->fonts.end(); it++)
		{
			glDeleteLists(it->second.list_base, 128);
			glDeleteTextures(128, &it->second.textures.front());
		}

		FT_Done_Face(this->face);
		FT_Done_FreeType(this->ft);
	}


	void set_window_width(int w) { this->width = w; }
	void set_window_height(int h) { this->height = h; }

	void draw_shape(GLfloat* verts, int vertCount, GLuint* indecies, int indeCount, int drawMode = GL_TRIANGLES)
	{
		glGenVertexArrays(1, &this->VAO);
		glGenBuffers(1, &this->VBO);
		glBindVertexArray(this->VAO);

		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, vertCount * sizeof(GLfloat), verts, GL_STATIC_DRAW);

		//Create IBO
		glGenBuffers(1, &this->IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indeCount * sizeof(GLuint), indecies, GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IBO);
		glDrawElements(drawMode, indeCount, GL_UNSIGNED_INT, NULL);

		glDeleteBuffers(1, &IBO);
		glDeleteBuffers(1, &VBO);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		glDeleteVertexArrays(1, &this->VAO);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void set_clear_colour(SDL_Color color) { glClearColor(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f); }

	void draw_rounded_rect(float x, float y, float w, float h, float r, SDL_Color color)
	{
		// Radius Limits
		float maxRadius = std::fminf(w, h);
		if (r > maxRadius) r = maxRadius;
		if (r < 0) r = 0;

		float x1 = get_relative_x(x);
		float y1 = get_relative_y(y);
		float x2 = get_relative_x(x + w);
		float y2 = get_relative_y(y + h);

		float ix1 = get_relative_x(x + r);
		float iy1 = get_relative_y(y + r);
		float ix2 = get_relative_x(x + w - r);
		float iy2 = get_relative_y(y + h - r);

		GLfloat* vertices = new GLfloat[24]{
			ix1, y1,    // 0
			ix2, y1,	// 1
			x1, iy1,	// 2
			ix1, iy1,	// 3
			ix2, iy1,	// 4
			x2, iy1,	// 5
			x1, iy2,	// 6
			ix1, iy2,	// 7
			ix2, iy2,	// 8
			x2, iy2,	// 9
			ix1, y2,	// 10
			ix2, y2		// 11
		};

		GLuint* indexData = new GLuint[30]{
			4, 1, 0,
			4, 0, 3,
			7, 3, 2,
			2, 6, 7,
			8, 4, 3,
			3, 7, 8,
			4, 8, 9,
			9, 5, 4,
			11, 8, 7,
			11, 7, 10
		};

		this->shapeShader->bind();
		this->shapeShader->setColor("aColor", color);
		this->draw_shape(vertices, 24, indexData, 30);
		this->shapeShader->unbind();

		this->draw_filled_circle(x + r, y + r, r, color);
		this->draw_filled_circle(x + r, y + h - r, r, color);
		this->draw_filled_circle(x + w - r, y + r, r, color);
		this->draw_filled_circle(x + w - r, y + h - r, r, color);

		delete[] vertices;
		delete[] indexData;
	}

	void draw_filled_rect(float x, float y, float w, float h, SDL_Color color)
	{
		float x1 = get_relative_x(x);
		float y1 = get_relative_y(y);
		float x2 = get_relative_x(x + w);
		float y2 = get_relative_y(y + h);

		GLfloat* vertices = new GLfloat[8]{
			x1, y1,
			x1, y2,
			x2, y2,
			x2, y1
		};

		GLuint* indexData = new GLuint[6]{ 0, 1, 2,
											3, 0, 2 };

		this->shapeShader->bind();
		this->shapeShader->setColor("aColor", color);
		this->draw_shape(vertices, 8, indexData, 6);
		this->shapeShader->unbind();

		delete[] vertices;
		delete[] indexData;
	}

	void draw_rect(float x, float y, float w, float h, SDL_Color color)
	{
		float x1 = get_relative_x(x);
		float y1 = get_relative_y(y);
		float x2 = get_relative_x(x + w);
		float y2 = get_relative_y(y + h);

		glBegin(GL_LINE_LOOP);
		glColor3f(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f);
		glVertex3f(x1, y1, 0.0f);
		glVertex3f(x2, y1, 0.0f);
		glVertex3f(x2, y2, 0.0f);
		glVertex3f(x1, y2, 0.0f);
		glEnd();

	}

	void draw_filled_quad(float x1, float y1, float x2, float y2, SDL_Color color)
	{
		float xa = get_relative_x(x1);
		float ya = get_relative_y(y1);
		float xb = get_relative_x(x2);
		float yb = get_relative_y(y2);

		GLfloat* vertices = new GLfloat[8]{
			xa, ya,
			xa, yb,
			xb, yb,
			xb, ya
		};

		GLuint* indexData = new GLuint[6]{ 0, 1, 2,
										   3, 0, 2 };

		this->shapeShader->bind();
		this->shapeShader->setColor("aColor", color);
		this->draw_shape(vertices, 8, indexData, 6);
		this->shapeShader->unbind();

		delete[] vertices;
		delete[] indexData;
	}

	void draw_filled_quad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, SDL_Color color)
	{
		float xa = get_relative_x(x1);
		float ya = get_relative_y(y1);
		float xb = get_relative_x(x2);
		float yb = get_relative_y(y2);
		float xc = get_relative_x(x3);
		float yc = get_relative_y(y3);
		float xd = get_relative_x(x4);
		float yd = get_relative_y(y4);

		GLfloat* vertices = new GLfloat[8]{
			xa, ya,
			xb, yb,
			xc, yc,
			xd, yd
		};

		GLuint* indexData = new GLuint[6]{ 0, 1, 2,
											2, 3, 0 };

		this->shapeShader->bind();
		this->shapeShader->setColor("aColor", color);
		this->draw_shape(vertices, 8, indexData, 6);
		this->shapeShader->unbind();

		delete[] vertices;
		delete[] indexData;
	}

	void draw_quad(float x1, float y1, float x2, float y2, SDL_Color color)
	{
		float xa = get_relative_x(x1);
		float ya = get_relative_y(y1);
		float xb = get_relative_x(x2);
		float yb = get_relative_y(y2);

		GLfloat* vertices = new GLfloat[8]{
			xa, ya,
			xa, yb,
			xb, yb,
			xb, ya
		};

		GLuint* indexData = new GLuint[6]{ 0, 1, 2,
											3, 0, 2 };

		this->shapeShader->bind();
		this->shapeShader->setColor("aColor", color);
		this->draw_shape(vertices, 8, indexData, 6, GL_LINE_LOOP);
		this->shapeShader->unbind();

		delete[] vertices;
		delete[] indexData;
	}

	void draw_quad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, SDL_Color color)
	{
		float xa = get_relative_x(x1);
		float ya = get_relative_y(y1);
		float xb = get_relative_x(x2);
		float yb = get_relative_y(y2);
		float xc = get_relative_x(x3);
		float yc = get_relative_y(y3);
		float xd = get_relative_x(x4);
		float yd = get_relative_y(y4);

		GLfloat* vertices = new GLfloat[8]{
			xa, ya,
			xb, yb,
			xc, yc,
			xd, yd
		};

		GLuint* indexData = new GLuint[6]{ 0, 1, 2,
										2, 3, 0 };

		this->shapeShader->bind();
		this->shapeShader->setColor("aColor", color);
		this->draw_shape(vertices, 8, indexData, 6, GL_LINE_LOOP);
		this->shapeShader->unbind();

		delete[] vertices;
		delete[] indexData;
	}

	void draw_filled_circle(float x, float y, float r, SDL_Color color)
	{
		float x1 = get_relative_x(x);
		float y1 = get_relative_y(y);

		float radiusx = r * 2.0f / this->width;
		float radiusy = r * 2.0f / this->height;

		const int steps = 100;
		const float angle = 3.1415926f * 2 / steps;

		float prevX = x1;
		float prevY = y1 + radiusy;

		for (int i = 0; i <= steps; i++) {
			float newX = x1 + radiusx * sin(angle * i);
			float newY = y1 - radiusy * cos(angle * i);

			glBegin(GL_TRIANGLES);
			glColor3f(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f);
			glVertex3f(x1, y1, 0.0f);
			glVertex3f(prevX, prevY, 0.0f);
			glVertex3f(newX, newY, 0.0f);
			glEnd();

			prevX = newX;
			prevY = newY;
		}
	}

	void draw_circle(float x, float y, float r, SDL_Color color)
	{
		float x1 = get_relative_x(x);
		float y1 = get_relative_y(y);

		float radiusx = r * 2.0f / this->width;
		float radiusy = r * 2.0f / this->height;

		const int steps = 100;
		const float angle = 3.1415926f * 2.0f / steps;

		float prevX = x1;
		float prevY = y1 + radiusy;

		for (int i = 0; i <= steps; i++) {
			float newX = x1 + radiusx * sin(angle * i);
			float newY = y1 - radiusy * cos(angle * i);

			if (prevX != newX) {

				glBegin(GL_LINES);
				glColor3f(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f);
				glVertex3f(prevX, prevY, 0.0f);
				glVertex3f(newX, newY, 0.0f);
				glEnd();
			}

			prevX = newX;
			prevY = newY;
		}
	}

	void draw_filled_triangle(float x1, float y1, float x2, float y2, float x3, float y3, SDL_Color color)
	{

		float xa = get_relative_x(x1);
		float ya = get_relative_y(y1);
		float xb = get_relative_x(x2);
		float yb = get_relative_y(y2);
		float xc = get_relative_x(x3);
		float yc = get_relative_y(y3);

		GLfloat* vertices = new GLfloat[6]{
			xa, ya,
			xb, yb,
			xc, yc
		};

		GLuint* indexData = new GLuint[3]{ 0, 1, 2 };

		this->shapeShader->bind();
		this->shapeShader->setColor("aColor", color);
		this->draw_shape(vertices, 6, indexData, 3);
		this->shapeShader->unbind();

		delete[] vertices;
		delete[] indexData;
	}

	void draw_triangle(float x1, float y1, float x2, float y2, float x3, float y3, SDL_Color color)
	{
		float xa = get_relative_x(x1);
		float ya = get_relative_y(y1);
		float xb = get_relative_x(x2);
		float yb = get_relative_y(y2);
		float xc = get_relative_x(x3);
		float yc = get_relative_y(y3);

		GLfloat* vertices = new GLfloat[6]{
			xa, ya,
			xb, yb,
			xc, yc
		};

		GLuint* indexData = new GLuint[3]{ 0, 1, 2 };

		this->shapeShader->bind();
		this->shapeShader->setColor("aColor", color);
		this->draw_shape(vertices, 6, indexData, 3, GL_LINE_LOOP);
		this->shapeShader->unbind();

		delete[] vertices;
		delete[] indexData;
	}

	void draw_text(std::string text, float x, float y, int size, SDL_Color color, std::string fontfamily = "res\\Fonts\\OpenSans\\OpenSansRegular.ttf", float linespace = 1.15f)
	{
		font_data temp = text_init(fontfamily, size);
		glColor3f((float)color.r / 255.0f, (float)color.g / 255.0f, (float)color.b / 255.0f);

		glPushAttrib(GL_TRANSFORM_BIT);
		GLint viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(viewport[0], viewport[2], viewport[1], viewport[3]);
		glPopAttrib();

		GLuint font = temp.list_base;
		float h = temp.height * linespace;

		std::stringstream ss(text);
		std::string to;
		std::vector<std::string> lines;
		while (std::getline(ss, to, '\n')) lines.push_back(to);

		glPushAttrib(GL_LIST_BIT | GL_CURRENT_BIT | GL_ENABLE_BIT | GL_TRANSFORM_BIT);
		glMatrixMode(GL_MODELVIEW);
		glDisable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glListBase(font);

		float modelview_matrix[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, modelview_matrix);

		for (unsigned int i = 0; i < lines.size(); i++) {
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(x, this->height - y - h * i, 0);
			glMultMatrixf(modelview_matrix);

			glCallLists(lines[i].length(), GL_UNSIGNED_BYTE, lines[i].c_str());
			glPopMatrix();
		}

		glPopAttrib();

		glPushAttrib(GL_TRANSFORM_BIT);
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glPopAttrib();
	}

	void draw_line(float x1, float y1, float x2, float y2, SDL_Color color, float thickness)
	{
		float x1a, y1a, x1b, y1b, x2a, y2a, x2b, y2b;
		float temp;

		float halfThickness = thickness / 2;

		/// First Coord Calcs
		float tempx1 = x2 - x1;
		float tempy1 = y2 - y1;

		temp = tempx1;
		tempx1 = -tempy1;
		tempy1 = temp;

		temp = std::sqrtf(tempx1 * tempx1 + tempy1 * tempy1);
		tempx1 /= temp;
		tempy1 /= temp;

		x1a = x1 + (tempx1 * halfThickness);
		y1a = y1 + (tempy1 * halfThickness);
		x1b = x1 - (tempx1 * halfThickness);
		y1b = y1 - (tempy1 * halfThickness);

		// Second Coord Calcs
		float tempx2 = x1 - x2;
		float tempy2 = y1 - y2;

		temp = tempx2;
		tempx2 = -tempy2;
		tempy2 = temp;

		temp = std::sqrtf(tempx2 * tempx2 + tempy2 * tempy2);
		tempx2 /= temp;
		tempy2 /= temp;

		x2a = x2 + (tempx2 * halfThickness);
		y2a = y2 + (tempy2 * halfThickness);
		x2b = x2 - (tempx2 * halfThickness);
		y2b = y2 - (tempy2 * halfThickness);

		this->draw_filled_quad(x1a, y1a, x2b, y2b, x2a, y2a, x1b, y1b, color);
	}

	float get_relative_x(float x)
	{
		return x * 2.0f / this->width - 1.0f;
	}

	float get_relative_y(float y)
	{
		return 1.0f - y * 2.0f / this->height;
	}

private:
	struct font_data {
		float height;
		std::vector<GLuint> textures;
		GLuint list_base;
	};


	int width, height;
	FT_Library ft;
	FT_Face face;

	std::map<const char*, font_data> fonts;

	Shader* shapeShader = nullptr;
	Shader* textShader = nullptr;

	GLuint VAO = 0, VBO = 0, IBO = 0;

	font_data text_init(std::string font, int size)
	{
		std::string key = font + ":" + std::to_string(size);
		std::map<const char*, font_data>::iterator it = fonts.find(key.c_str());
		if (it != fonts.end()) {
			return fonts[key.c_str()];
		}

		font_data newFont;
		newFont.textures.resize(128);
		newFont.height = (float)size;

		FT_Library library;
		FATAL_ASSERT_MESS(!FT_Init_FreeType(&library), "FT_Init_FreeType failed");

		FT_Face face;
		FATAL_ASSERT_MESS(!FT_New_Face(library, font.c_str(), 0, &face), "FT_New_Face failed");

		FT_Set_Char_Size(face, size << 6, size << 6, 96, 96);

		newFont.list_base = glGenLists(128);
		glGenTextures(128, &newFont.textures.front());

		for (unsigned char i = 0; i < 128; i++) {
			text_make_textures(face, i, newFont.list_base, &newFont.textures.front());
		}

		fonts.insert(std::pair<const char*, font_data>(key.c_str(), newFont));

		FT_Done_Face(face);
		FT_Done_FreeType(library);
		return newFont;
	}

	void text_make_textures(FT_Face face, char ch, GLuint list_base, GLuint* tex_base)
	{
		FATAL_ASSERT_MESS(!FT_Load_Glyph(face, FT_Get_Char_Index(face, ch), FT_LOAD_DEFAULT), "FT_Load_Glyph failed");

		FT_Glyph glyph;
		FATAL_ASSERT_MESS(!FT_Get_Glyph(face->glyph, &glyph), "FT_Get_Glyph failed");

		FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
		FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;

		FT_Bitmap& bitmap = bitmap_glyph->bitmap;

		auto next_power_2 = [](unsigned int x) {
			unsigned int rval = 1;
			while (rval < x) rval <<= 1;
			return rval;
		};

		int width = next_power_2(bitmap.width);
		int height = next_power_2(bitmap.rows);

		std::vector<GLubyte> expanded_data(2 * width * height, 0);
		for (int j = 0; j < height; j++) {
			for (int i = 0; i < width; i++) {
				expanded_data[2 * (i + j * width)] = 255;
				expanded_data[2 * (i + j * width) + 1] =
					(i >= (int)bitmap.width || j >= (int)bitmap.rows) ? 0 :
					bitmap.buffer[i + bitmap.width * j];
			}
		}

		glBindTexture(GL_TEXTURE_2D, tex_base[ch]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, &expanded_data.front());

		glNewList(list_base + ch, GL_COMPILE);
		glBindTexture(GL_TEXTURE_2D, tex_base[ch]);

		glPushMatrix();

		glTranslatef((GLfloat)bitmap_glyph->left, 0.0f, 0.0f);
		glTranslatef(0, bitmap_glyph->top - (bitmap.rows * 0.9f), 0);

		float x = (float)bitmap.width / (float)width,
			y = (float)bitmap.rows / (float)height;

		glBegin(GL_QUADS);
		glTexCoord2d(0, 0); glVertex2i(0, bitmap.rows);
		glTexCoord2d(0, y); glVertex2f(0, 0);
		glTexCoord2d(x, y); glVertex2i(bitmap.width, 0);
		glTexCoord2d(x, 0); glVertex2i(bitmap.width, bitmap.rows);
		glEnd();

		glPopMatrix();

		glTranslatef((GLfloat)(face->glyph->advance.x >> 6), 0, 0);

		glEndList();
	}
};