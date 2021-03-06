// Copyright (c) 2016-2018 Easy2D - Nomango
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "..\e2dobject.h"
#include "..\e2dmodule.h"

easy2d::Canvas::Canvas(float width, float height)
	: render_target_(nullptr)
	, fill_brush_(nullptr)
	, line_brush_(nullptr)
	, stroke_style_(nullptr)
	, stroke_width_(1.0f)
	, stroke_(Stroke::Miter)
{
	render_target_ = Device::GetGraphics()->GetRenderTarget();
	render_target_->AddRef();

	ThrowIfFailed(
		render_target_->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::White),
			&fill_brush_
		)
	);

	ThrowIfFailed(
		render_target_->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::White),
			&line_brush_
		)
	);
	
	this->SetClipEnabled(true);
	this->SetWidth(width);
	this->SetHeight(height);
	this->SetStrokeStyle(stroke_);
}

easy2d::Canvas::~Canvas()
{
	SafeRelease(line_brush_);
	SafeRelease(fill_brush_);
	SafeRelease(render_target_);
}

void easy2d::Canvas::SetLineColor(const Color & color)
{
	line_brush_->SetColor(D2D_COLOR_F(color));
}

void easy2d::Canvas::SetFillColor(const Color & color)
{
	fill_brush_->SetColor(D2D_COLOR_F(color));
}

void easy2d::Canvas::SetStrokeWidth(float width)
{
	stroke_width_ = std::max(width, 0.f);
}

void easy2d::Canvas::SetStrokeStyle(Stroke strokeStyle)
{
	switch (strokeStyle)
	{
	case easy2d::Stroke::Miter:
		stroke_style_ = Device::GetGraphics()->GetMiterStrokeStyle();
		break;
	case easy2d::Stroke::Bevel:
		stroke_style_ = Device::GetGraphics()->GetBevelStrokeStyle();
		break;
	case easy2d::Stroke::Round:
		stroke_style_ = Device::GetGraphics()->GetRoundStrokeStyle();
		break;
	}
}

easy2d::Color easy2d::Canvas::GetLineColor() const
{
	return line_brush_->GetColor();
}

easy2d::Color easy2d::Canvas::GetFillColor() const
{
	return fill_brush_->GetColor();
}

float easy2d::Canvas::GetStrokeWidth() const
{
	return stroke_width_;
}

easy2d::Stroke easy2d::Canvas::GetStrokeStyle() const
{
	return stroke_;
}

void easy2d::Canvas::DrawLine(const Point & begin, const Point & end)
{
	render_target_->DrawLine(
		D2D1::Point2F(begin.x, begin.y),
		D2D1::Point2F(end.x, end.y),
		line_brush_,
		stroke_width_,
		stroke_style_
	);
}

void easy2d::Canvas::DrawCircle(const Point & center, float radius)
{
	render_target_->DrawEllipse(
		D2D1::Ellipse(
			D2D1::Point2F(
				center.x,
				center.y
			),
			radius,
			radius
		),
		line_brush_,
		stroke_width_,
		stroke_style_
	);
}

void easy2d::Canvas::DrawEllipse(const Point & center, float radius_x, float radius_y)
{
	render_target_->DrawEllipse(
		D2D1::Ellipse(
			D2D1::Point2F(
				center.x,
				center.y
			),
			radius_x,
			radius_y
		),
		line_brush_,
		stroke_width_,
		stroke_style_
	);
}

void easy2d::Canvas::DrawRect(const Rect & rect)
{
	render_target_->DrawRectangle(
		D2D1::RectF(
			rect.origin.x,
			rect.origin.y,
			rect.origin.x + rect.size.width,
			rect.origin.y + rect.size.height
		),
		line_brush_,
		stroke_width_,
		stroke_style_
	);
}

void easy2d::Canvas::DrawRoundedRect(const Rect & rect, float radius_x, float radius_y)
{
	render_target_->DrawRoundedRectangle(
		D2D1::RoundedRect(
			D2D1::RectF(
				rect.origin.x,
				rect.origin.y,
				rect.origin.x + rect.size.width,
				rect.origin.y + rect.size.height
			),
			radius_x,
			radius_y
		),
		line_brush_,
		stroke_width_,
		stroke_style_
	);
}

void easy2d::Canvas::FillCircle(const Point & center, float radius)
{
	render_target_->FillEllipse(
		D2D1::Ellipse(
			D2D1::Point2F(
				center.x,
				center.y
			),
			radius,
			radius
		),
		fill_brush_
	);
}

void easy2d::Canvas::FillEllipse(const Point & center, float radius_x, float radius_y)
{
	render_target_->FillEllipse(
		D2D1::Ellipse(
			D2D1::Point2F(
				center.x,
				center.y
			),
			radius_x,
			radius_y
		),
		fill_brush_
	);
}

void easy2d::Canvas::FillRect(const Rect & rect)
{
	render_target_->FillRectangle(
		D2D1::RectF(
			rect.origin.x,
			rect.origin.y,
			rect.origin.x + rect.size.width,
			rect.origin.y + rect.size.height
		),
		fill_brush_
	);
}

void easy2d::Canvas::FillRoundedRect(const Rect & rect, float radius_x, float radius_y)
{
	render_target_->FillRoundedRectangle(
		D2D1::RoundedRect(
			D2D1::RectF(
				rect.origin.x,
				rect.origin.y,
				rect.origin.x + rect.size.width,
				rect.origin.y + rect.size.height
			),
			radius_x,
			radius_y
		),
		fill_brush_
	);
}
