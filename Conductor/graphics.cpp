#include "graphics.h"

Model Graphics::m_track_plane;
RenderTexture2D Graphics::m_track_plane_tex;

void Graphics::init()
{
	Mesh planeMesh = GenMeshPlane(1.0f, 16.0f, 1, 1);
	m_track_plane = LoadModelFromMesh(planeMesh);
	m_track_plane_tex = LoadRenderTexture(512, 64);
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
	for (int i = 0; (iterator != track.getEnd()) && (i < 16); iterator++, i++)
	{
		if (*iterator)
			DrawRectangle(i * 32, 0, 32, 512, BLUE);
	}
}

void Graphics::renderTrack()
{
	// TODO: tarviiko tätä oikeasti tehdä aina vai riittääkö että tekee kerran
	SetMaterialTexture(m_track_plane.materials, 0, m_track_plane_tex.texture);

	Vector3 pos = { 0.0f, 0.0f, 0.0f };

	DrawModel(m_track_plane, pos, 1.0, RED);
}