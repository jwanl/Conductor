#include "graphics.h"
#include <cmath>
#include <iostream>
Model Graphics::m_track_plane;
RenderTexture2D Graphics::m_track_plane_tex;
Texture2D Graphics::m_background_tex;

void Graphics::init(const char* backgroundTexture)
{
	Mesh planeMesh = GenMeshPlane(8.0f, 0.5f, 1, 1);
	m_track_plane = LoadModelFromMesh(planeMesh);
	m_track_plane_tex = LoadRenderTexture(512, 64);
	SetMaterialTexture(m_track_plane.materials, 0, m_track_plane_tex.texture);

	m_background_tex = LoadTexture(backgroundTexture);
}

RenderTexture2D& Graphics::getTrackRenderTexture()
{
	return m_track_plane_tex;
}

/* Draws to track render texture. Remember to change drawing mode first and after */
void Graphics::drawRenderTexture(Track& track)
{
	ClearBackground(ColorAlpha(WHITE, 0.4f));
	
	auto sub = track.getNextValues();
	double leftSide = track.getTime();

	for (int i = 0; i < 4; i++) {
		const auto y = i * 64 / 4;
		DrawLine(0, y, 511, y, ColorAlpha(BLACK, 0.8f));
	}
	DrawLine(0, 63, 511, 63, ColorAlpha(BLACK, 0.8f));

	for (const auto& item : sub)
	{
		
		const auto& tex = track.m_objects[item.i];
		//DrawTextureEx(tex, { (item.x - (float)leftSide) * 128.0f, item.y * 64.0f + 32.0f }, 180.0f, 1.0f, WHITE);
		DrawTextureRec(tex, Rectangle{ 0, 0  , (float)tex.width, -(float)tex.height }, { (item.x - (float)leftSide) * 128.0f, item.y * 64.0f + 32.0f }, GREEN);
		//DrawTexture(tex, (item.x - leftSide) * 128, item.y * 64 + 32, WHITE);
		//DrawCircle((item.x - leftSide) * 128, item.y * 64 + 32, 8, BLUE);


	}

	
	
}

void Graphics::renderTrack()
{
	Vector3 pos = { 1.8f, 0.3f, 0.3f };
	Vector3 rax = { 0.970f, 0.0f, 0.0242f };
	Vector3 size = { 1.0f, 1.0f, 1.0f };

	DrawModelEx(m_track_plane, pos, rax, 185.539f, size, WHITE);
}




void Graphics::drawBackground()
{
	
	/*const auto t = GetTime();
	const auto dx = std::sin(t * 200) + std::cos(t * 17);
	const auto dy = std::cos(t * 20) + std::sin(t * 150);
	DrawTexture(m_background_tex, 10 * dx, 10 * dy, WHITE);*/
	DrawTexture(m_background_tex, 0, 0, WHITE);
}