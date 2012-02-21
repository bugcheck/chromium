// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/ui/window_snapshot/window_snapshot.h"

#include "ash/shell.h"
#include "base/logging.h"
#include "third_party/skia/include/core/SkBitmap.h"
#include "ui/aura/window.h"
#include "ui/gfx/codec/png_codec.h"
#include "ui/gfx/compositor/compositor.h"
#include "ui/gfx/rect.h"

namespace browser {

bool GrabWindowSnapshot(gfx::NativeWindow window,
                        std::vector<unsigned char>* png_representation,
                        const gfx::Rect& snapshot_bounds) {
  ui::Compositor* compositor = window->layer()->GetCompositor();

  gfx::Rect read_pixels_bounds = snapshot_bounds;

  // When not in compact mode we must take into account the window's position on
  // the desktop.
  if (!ash::Shell::GetInstance()->IsWindowModeCompact())
    read_pixels_bounds.set_origin(
        snapshot_bounds.origin().Add(window->bounds().origin()));

  DCHECK_GE(compositor->size().width(), read_pixels_bounds.right());
  DCHECK_GE(compositor->size().height(), read_pixels_bounds.bottom());
  DCHECK_LE(0, read_pixels_bounds.x());
  DCHECK_LE(0, read_pixels_bounds.y());

  SkBitmap bitmap;
  if (!compositor->ReadPixels(&bitmap, read_pixels_bounds))
    return false;

  unsigned char* pixels = reinterpret_cast<unsigned char*>(bitmap.getPixels());

  gfx::PNGCodec::Encode(pixels, gfx::PNGCodec::FORMAT_BGRA,
                        snapshot_bounds.size(),
                        bitmap.rowBytes(), true,
                        std::vector<gfx::PNGCodec::Comment>(),
                        png_representation);
  return true;
}

}  // namespace browser
