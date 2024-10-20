#include "graphics.h"
#include <cmath>
#include <iostream>
Model Graphics::m_track_plane;
RenderTexture2D Graphics::m_track_plane_tex;
Texture2D Graphics::m_background_tex;
std::vector<Texture2D> Graphics::m_conductor_sprites;
int Graphics::m_conductor_anim_phase;
int Graphics::m_conductor_anim_target;
bool Graphics::m_conductor_baton_prev;
float Graphics::m_tick_time;
float Graphics::m_shake_multiplier;
float Graphics::m_hit_timer;
bool Graphics::m_prev_hit;

void Graphics::init(const char* backgroundTexture, std::vector<std::string> conductorSprites)
{
	Mesh planeMesh = GenMeshPlane(8.0f, 0.5f, 1, 1);
	m_track_plane = LoadModelFromMesh(planeMesh);
	m_track_plane_tex = LoadRenderTexture(512, 64);
	SetMaterialTexture(m_track_plane.materials, 0, m_track_plane_tex.texture);

	m_background_tex = LoadTexture(backgroundTexture);

	// load conductor sprite sheet
	for (auto& sprite : conductorSprites)
	{
		m_conductor_sprites.push_back(LoadTexture(sprite.c_str()));
	}

	m_conductor_anim_phase = 0;
	m_conductor_anim_target = 0;
	m_conductor_baton_prev = false;
	m_tick_time = 0.0f;
	m_shake_multiplier = 0.0f;
	m_hit_timer = 0.0f;
	m_prev_hit = false;
}

RenderTexture2D& Graphics::getTrackRenderTexture()
{
	return m_track_plane_tex;
}

/* Draws to track render texture. Remember to change drawing mode first and after */
void Graphics::drawRenderTexture(Track& track)
{
	/*const auto fadout = 5.0f;
	 auto overtime = track.m_time - (track.getLength() - fadout);
	 overtime = overtime < 0.4f ? 0.4f : overtime;
	 std::cout << overtime << "\n";
	 auto a = 1.0f - overtime * 0.3;*/
	ClearBackground(ColorAlpha(WHITE, 0.4f));

	for (int i = 0; i < 4; i++) {
		const auto y = i * 64 / 4;
		DrawLine(0, y, 511, y, ColorAlpha(BLACK, 0.8f));
	}
	DrawLine(0, 63, 511, 63, ColorAlpha(BLACK, 0.8f));

	
	
	auto sub = track.getNextValues();
	double leftSide = track.getTime();

	

	
	for (const auto& item : sub)
	{
		if (item.x > (track.getLength() - 2.0f)) {
			break;
		}
		const auto& tex = track.m_objects[item.i];
		//DrawTextureEx(tex, { (item.x - (float)leftSide) * 128.0f, item.y * 64.0f + 32.0f }, 180.0f, 1.0f, WHITE);
		DrawTextureRec(tex, Rectangle{ 0, 0  , (float)tex.width, -(float)tex.height }, { (item.x - (float)leftSide) * 128.0f, item.y * 64.0f + 32.0f }, WHITE);
		//DrawTexture(tex, (item.x - leftSide) * 128, item.y * 64 + 32, WHITE);
		//DrawCircle((item.x - leftSide) * 128, item.y * 64 + 32, 8, BLUE);	
	}
}

void Graphics::drawHitLine(Level& level)
{
	m_shake_multiplier = std::max(m_shake_multiplier - GetFrameTime(), 0.0f);
	m_hit_timer = std::max(m_hit_timer - GetFrameTime(), 0.0f);

	if (level.getHit()) 
	{
		m_hit_timer = 0.8f;
		m_prev_hit = true;
	}
	else if (level.getMiss())
	{
		m_shake_multiplier = 2.0f;
		m_hit_timer = 0.8f;
		m_prev_hit = false;
	}

	if (!m_prev_hit)
		DrawRectangle(0, 0, 2, 64, ColorAlpha(RED, 0.85f * m_hit_timer));
	else
		DrawRectangle(0, 0, 2, 64, ColorAlpha(GREEN, 0.85f * m_hit_timer));
}


void Graphics::renderTrack()
{
	// demo code to find a good orientation for track plane
	//if (IsKeyDown(KEY_M)) angle += 1.0f;
	//if (IsKeyDown(KEY_N)) angle -= 1.0f;
	//if (IsKeyDown(KEY_LEFT)) rax.x += 0.005f;
	//if (IsKeyDown(KEY_RIGHT)) rax.x -= 0.005f;
	//if (IsKeyDown(KEY_UP)) rax.y += .005f;
	//if (IsKeyDown(KEY_DOWN)) rax.y -= .005f;
	//if (IsKeyDown(KEY_O)) rax.z += .005f;
	//if (IsKeyDown(KEY_L)) rax.z -= .005f;

	Vector3 pos = { 0.8f, -2.25f, 0.1f };
	Vector3 rax = { 0.93099f, -0.365046f, 0.0f };
	float angle = 180.0f + 0.5f * std::sin(GetTime() * 0.5f);
	//rax = Vector3Normalize(rax);
	//std::cout << rax.x << " : " << rax.y << " : " << rax.z << "\n";

	Vector3 size = { 1.0f, 1.0f, 1.0f };

	DrawModelEx(m_track_plane, pos, rax, angle, size, WHITE);
}




void Graphics::drawBackground()
{
	const float t = (float)GetTime();
	const float dx = (std::sin(t * 200.0f) + std::sin(t * 17.0f)) * m_shake_multiplier;
	const float dy = (std::sin(t * 20.0f) + std::sin(t * 150.0f)) * m_shake_multiplier;
	DrawTextureV(m_background_tex, { 10 * dx, 10 * dy }, WHITE);
	//DrawTexture(m_background_tex, 0, 0, WHITE);
}

void Graphics::drawConductor(Level& level)
{
	if (level.isBatonUp() && !m_conductor_baton_prev)
	{
		m_conductor_anim_target = 2;
		m_conductor_baton_prev = true;
	}
	else if (!level.isBatonUp() && m_conductor_baton_prev)
	{
		m_conductor_anim_target = 0;
		m_conductor_baton_prev = false;
	}

	// update animation phase
	if (updateAnimationTick())
	{
		if (m_conductor_anim_phase < m_conductor_anim_target)
			m_conductor_anim_phase++;
		else if (m_conductor_anim_phase > m_conductor_anim_target)
			m_conductor_anim_phase--;
	}

	float scale = 1.5f;

	DrawTextureEx(m_conductor_sprites.at(m_conductor_anim_phase), 
		{ (float)GetRenderWidth() / 2.0f - (128.0f * scale), (float)GetRenderHeight() - 350.0f },
		0.0f, scale, WHITE);
}

void Graphics::drawProgressBar(float percentage) {
	DrawRectangle(0, GetRenderHeight() - 3, (int)(GetRenderWidth() * percentage), 3, GREEN);
}

bool Graphics::updateAnimationTick()
{
	m_tick_time += GetFrameTime();
	if (m_tick_time > ANIMATION_TICK_INTERVAL)
	{
		m_tick_time -= ANIMATION_TICK_INTERVAL;
		return true;
	}
	return false;
}