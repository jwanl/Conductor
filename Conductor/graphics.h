#pragma once

#include "track.h"
#include "raylib.h"

class Graphics {
public:
	static void init();
	static void drawRenderTexture(Track& track);
	static void renderTrack();
	static RenderTexture2D& getTrackRenderTexture();
private:
	static Model m_track_plane;
	static RenderTexture2D m_track_plane_tex;
};