#include "graphics.h"

Model Graphics::m_track_plane;
RenderTexture2D Graphics::m_track_plane_tex;

void Graphics::init()
{
	Mesh planeMesh = GenMeshPlane(8.0f, 1.0f, 1, 1);
	m_track_plane = LoadModelFromMesh(planeMesh);
	m_track_plane_tex = LoadRenderTexture(256, 32);
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
	
	auto iterator = track.getCurrentValue();
	for (int i = 0; (iterator != track.getEnd()) || (i < 16); iterator++, i++)
	{
		DrawRectangle(i * 16, *iterator ? 28 : 0, 16, 4, BLUE);
	}
}

void Graphics::renderTrack()
{
	Vector3 pos = { 2.0f, 0.2f, 0.4f };
	Vector3 rax = { 1.0f, 0.0f, 0.0f };
	Vector3 size = { 1.0f, 1.0f, 1.0f };

	DrawModelEx(m_track_plane, pos, rax, 270.0f, size, WHITE);
}