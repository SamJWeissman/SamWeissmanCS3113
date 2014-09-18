class Entity {
public:
	typedef struct {
		float x;
		float y;
		float r;
		float g;
		float b;
	} Vertex2D;

	float x;
	float y;
	float rotation;
	GLuint textureID;
	float width;
	float height;
	float speed;
	float direction_x;
	float direction_y;
	Entity(float xPos, float yPos, float rot, GLuint texture, float w, float h, float spd, float dir_x, float dir_y) : x(xPos), y(yPos), rotation(rot), textureID(texture), width(w), height(h), speed(spd), direction_x(dir_x), direction_y(dir_y){}

	/*void DrawByTexture(GLuint texture, float x, float y, float width, float height)
	{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(x, y, 0.0);
	//glRotatef(rotation, 0.0, 0.0, 1.0);
	GLfloat quad[] = { -width / 2.0f, height / 2.0f , -width / 2.0f, -height / 2.0f, width / 2.0f, -height / 2.0f, width / 2.0f, height / 2.0f};
	glVertexPointer(2, GL_FLOAT, 0, quad);
	glEnableClientState(GL_VERTEX_ARRAY);
	GLfloat quadUVs[] = { 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0 };
	glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawArrays(GL_QUADS, 0, 4);
	glDisable(GL_TEXTURE_2D);
	}*/

	void drawByQuad()
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(x, y, 0.0);
		Vertex2D quadData[4] = { { -width / 2.0f, height / 2.0f, 1.0f, 1.0f, 1.0f }, { -width / 2.0f, -height / 2.0f, 1.0f, 1.0f, 1.0f }, { width / 2.0f, -height / 2.0f, 1.0f, 1.0f, 1.0f }, { width / 2.0f, height / 2.0f, 1.0f, 1.0f, 1.0f } };
		glVertexPointer(4, GL_FLOAT, sizeof(float) * 5, quadData);
		glEnableClientState(GL_VERTEX_ARRAY);
		glColorPointer(3, GL_FLOAT, sizeof(float) * 5, &quadData[0].r);
		glEnableClientState(GL_COLOR_ARRAY);
		glDrawArrays(GL_QUADS, 0, 4);
		glDisable(GL_VERTEX_ARRAY);
		glDisable(GL_COLOR_ARRAY);
	}

	bool checkEntitytoEntityCollision(Entity* other)
	{
		if (y - (height / 2.0f) > (other->y + ((other->height) / 2.0f)) || (y + (height / 2.0f) < (other->y - ((other->height) / 2.0f))) || (x - (width / 2.0f) > (other->x + ((other->width) / 2.0f))) || (x + (width / 2.0f) < (other->x - ((other->width) / 2.0f)))) 
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	void checkVerticalWallCollision()
	{
		if (y + (height / 2.0f) >= 0.8f || y - (height / 2.0f) <= -0.8f)
		{
			direction_y *= -1.0f;
		}
	}

	void move(float elapsed)
	{
		x += direction_x * elapsed * speed;
		y += direction_y * elapsed * speed;
	}

};
