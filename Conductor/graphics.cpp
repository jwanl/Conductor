#include "graphics.h"

Model Graphics::m_track_plane;
RenderTexture2D Graphics::m_track_plane_tex;

void Graphics::init()
{
	Mesh planeMesh = GenMeshPlane(8.0f, 0.5f, 1, 1);
	m_track_plane = LoadModelFromMesh(planeMesh);
	m_track_plane_tex = LoadRenderTexture(512, 64);
	SetMaterialTexture(m_track_plane.materials, 0, m_track_plane_tex.texture);
}

RenderTexture2D& Graphics::getTrackRenderTexture()
{
	return m_track_plane_tex;
}

/* Draws to track render texture. Remember to change drawing mode first and after */
void Graphics::drawRenderTexture(Track& track)
{
	ClearBackground(WHITE);
	
	auto sub = track.getNextValues();
	double leftSide = track.getTime();
	for (Vector2& item : sub)
	{
		DrawCircle((item.x - leftSide) * 64, item.y * 64 + 32, 8, BLUE);
	}
}

void Graphics::renderTrack()
{
	Vector3 pos = { 1.8f, 0.3f, 0.3f };
	Vector3 rax = { 0.970f, 0.0f, 0.0242f };
	Vector3 size = { 1.0f, 1.0f, 1.0f };

	DrawModelEx(m_track_plane, pos, rax, 185.539f, size, WHITE);
}