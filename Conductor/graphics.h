#pragma once

#include "track.h"
#include "raylib.h"
#include "raymath.h"

class Graphics {
public:
	static void init(const char* backgroundTexture);
	static void drawRenderTexture(Track& track);
	static void renderTrack();
	static RenderTexture2D& getTrackRenderTexture();
	static void drawBackground();
private:
	static Model m_track_plane;
	static RenderTexture2D m_track_plane_tex;
	static Texture2D m_background_tex;
};