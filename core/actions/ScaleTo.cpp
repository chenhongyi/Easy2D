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

#include "..\e2daction.h"
#include "..\e2dobject.h"

easy2d::ScaleTo::ScaleTo(float duration, float scale)
	: ScaleBy(duration, 0, 0)
{
	end_scale_x_ = scale;
	end_scale_y_ = scale;
}

easy2d::ScaleTo::ScaleTo(float duration, float scale_x, float scale_y)
	: ScaleBy(duration, 0, 0)
{
	end_scale_x_ = scale_x;
	end_scale_y_ = scale_y;
}

easy2d::ScaleTo * easy2d::ScaleTo::Clone() const
{
	return new ScaleTo(duration_, end_scale_x_, end_scale_y_);
}

void easy2d::ScaleTo::Init()
{
	ScaleBy::Init();
	delta_x_ = end_scale_x_ - start_scale_x_;
	delta_y_ = end_scale_y_ - start_scale_y_;
}
