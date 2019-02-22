/*
* Copyright 2006 The Android Open Source Project
*
* Use of this source code is governed by a BSD-style license that can be
* found in the LICENSE file.
*/

#ifndef SkGradientShader_DEFINED
#define SkGradientShader_DEFINED

#include "SkShader.h"

class SK_API SkGradientShader {
public:
	enum Flags {
		kInterpolateColorsInPremul_Flag = 1 << 0,
	};

	static sk_sp<SkShader> MakeLinear(const SkPoint pts[2],
		const SkColor colors[], const SkScalar pos[], int count,
		SkShader::TileMode mode,
		uint32_t flags, const SkMatrix* localMatrix);
	static sk_sp<SkShader> MakeLinear(const SkPoint pts[2],
		const SkColor colors[], const SkScalar pos[], int count,
		SkShader::TileMode mode) {
		return MakeLinear(pts, colors, pos, count, mode, 0, NULL);
	}

	static sk_sp<SkShader> MakeLinear(const SkPoint pts[2],
		const SkColor4f colors[], sk_sp<SkColorSpace> colorSpace,
		const SkScalar pos[], int count, SkShader::TileMode mode,
		uint32_t flags, const SkMatrix* localMatrix);
	static sk_sp<SkShader> MakeLinear(const SkPoint pts[2],
		const SkColor4f colors[], sk_sp<SkColorSpace> colorSpace,
		const SkScalar pos[], int count, SkShader::TileMode mode) {
		return MakeLinear(pts, colors, std::move(colorSpace), pos, count, mode, 0, NULL);
	}

	static sk_sp<SkShader> MakeRadial(const SkPoint& center, SkScalar radius,
		const SkColor colors[], const SkScalar pos[], int count,
		SkShader::TileMode mode,
		uint32_t flags, const SkMatrix* localMatrix);
	static sk_sp<SkShader> MakeRadial(const SkPoint& center, SkScalar radius,
		const SkColor colors[], const SkScalar pos[], int count,
		SkShader::TileMode mode) {
		return MakeRadial(center, radius, colors, pos, count, mode, 0, NULL);
	}

	static sk_sp<SkShader> MakeRadial(const SkPoint& center, SkScalar radius,
		const SkColor4f colors[], sk_sp<SkColorSpace> colorSpace,
		const SkScalar pos[], int count, SkShader::TileMode mode,
		uint32_t flags, const SkMatrix* localMatrix);
	static sk_sp<SkShader> MakeRadial(const SkPoint& center, SkScalar radius,
		const SkColor4f colors[], sk_sp<SkColorSpace> colorSpace,
		const SkScalar pos[], int count, SkShader::TileMode mode) {
		return MakeRadial(center, radius, colors, std::move(colorSpace), pos, count, mode, 0, NULL);
	}

	static sk_sp<SkShader> MakeTwoPointConical(const SkPoint& start, SkScalar startRadius,
		const SkPoint& end, SkScalar endRadius,
		const SkColor colors[], const SkScalar pos[],
		int count, SkShader::TileMode mode,
		uint32_t flags, const SkMatrix* localMatrix);
	static sk_sp<SkShader> MakeTwoPointConical(const SkPoint& start, SkScalar startRadius,
		const SkPoint& end, SkScalar endRadius,
		const SkColor colors[], const SkScalar pos[],
		int count, SkShader::TileMode mode) {
		return MakeTwoPointConical(start, startRadius, end, endRadius, colors, pos, count, mode,
			0, NULL);
	}

	static sk_sp<SkShader> MakeTwoPointConical(const SkPoint& start, SkScalar startRadius,
		const SkPoint& end, SkScalar endRadius,
		const SkColor4f colors[],
		sk_sp<SkColorSpace> colorSpace, const SkScalar pos[],
		int count, SkShader::TileMode mode,
		uint32_t flags, const SkMatrix* localMatrix);
	static sk_sp<SkShader> MakeTwoPointConical(const SkPoint& start, SkScalar startRadius,
		const SkPoint& end, SkScalar endRadius,
		const SkColor4f colors[],
		sk_sp<SkColorSpace> colorSpace, const SkScalar pos[],
		int count, SkShader::TileMode mode) {
		return MakeTwoPointConical(start, startRadius, end, endRadius, colors,
			std::move(colorSpace), pos, count, mode, 0, NULL);
	}

	static sk_sp<SkShader> MakeSweep(SkScalar cx, SkScalar cy,
		const SkColor colors[], const SkScalar pos[], int count,
		uint32_t flags, const SkMatrix* localMatrix);
	static sk_sp<SkShader> MakeSweep(SkScalar cx, SkScalar cy,
		const SkColor colors[], const SkScalar pos[], int count) {
		return MakeSweep(cx, cy, colors, pos, count, 0, NULL);
	}

	static sk_sp<SkShader> MakeSweep(SkScalar cx, SkScalar cy,
		const SkColor4f colors[], sk_sp<SkColorSpace> colorSpace,
		const SkScalar pos[], int count,
		uint32_t flags, const SkMatrix* localMatrix);
	static sk_sp<SkShader> MakeSweep(SkScalar cx, SkScalar cy,
		const SkColor4f colors[], sk_sp<SkColorSpace> colorSpace,
		const SkScalar pos[], int count) {
		return MakeSweep(cx, cy, colors, std::move(colorSpace), pos, count, 0, NULL);
	}
};

#endif