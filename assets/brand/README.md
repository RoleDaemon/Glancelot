# Glancelot | Slate & Ice asset pack

## Source of truth

The seven user-provided one-eyed knight illustrations are the **canonical designs**. This build preserves those RGBA PNG masters unchanged, without generative redraws or destructive recoloring. In particular, do not replace the **single eye** with two humanlike eyes.

The originals already have a cool silver/slate-blue appearance. Exact hex tokens below are for app themes and purpose-built vector icons; natural 3D illustration gradients need not equal one flat color value.

## Key directories

| Directory | Contents | Intended use |
|---|---|---|
| `sources/` | Exact uploaded master PNGs | Reference, provenance, re-builds |
| `mascots/transparent/` | Transparent 1024px PNG originals | App empty states and overlays |
| `mascots/webp/` | Lossless WebP, 1024px and 512px | Optimized application delivery |
| `mascots/light/` | 1024px JPG-preview-style PNGs on light background | Fixed-theme uses |
| `mascots/dark/` | 1024px PNGs on dark background | Fixed-theme uses |
| `icons/app/` | App icon SVGs, PNG sizes 16–1024, dark/light, PWA maskable, ICO, portrait alternate | Application launcher, browser favicon and OS assets |
| `icons/ui/currentColor/` | Theme-reactive vector UI SVGs | Primary recommended SVGs in the application |
| `icons/ui/light/`, `icons/ui/dark/` | Color-fixed variants of UI SVGs | Static media or surfaces that cannot inherit CSS |
| `previews/` | Contact sheets and icon overview | Visual quality inspection |
| `manifest.webmanifest` | Example progressive web app (PWA) manifest | Adapt URL paths when integrating |
| `theme.css`, `palette.json` | Tokens | Theme integration |
| `asset-manifest.json` | Asset dimensions, bounding boxes and SHA-256 hashes | Traceability and integrity |
| `build_asset_pack.py` | Reproducible pack generation | Rebuild when needed |

## Locked colors

| Mascot color | Hex |
|---|---|
| Navy | `#233246` |
| Slate | `#496E99` |
| Ice | `#8ABBD9` |
| Silver | `#C5D2DF` |
| Iris | `#439EE0` |

Light UI: background `#F4F7FA`, surface `#FFFFFF`, text `#233246`, primary `#496E99`, accent `#8ABBD9`, border `#DFE5ED`.

Dark UI: background `#101923`, surface `#1B2937`, text `#EAF3FB`, primary `#93BEE9`, accent `#93DCE4`, border `#33465A`.

## Mascot usage

1. Standing: home/default/empty state.
2. Waving: welcome/onboarding.
3. Holding photo: image library/gallery.
4. Zoom: zoom/search.
5. Success: completed work/success toast.
6. Thinking: help/tips.
7. Portrait: about screen, mascot profile, illustrated app icon alternate.

**Image handling:** Prefer transparent master PNG for fidelity, or lossless WebP for delivery. Keep `object-fit: contain`; do not crop the cape/plume. The original 1024 canvases align artwork consistently, with ~6.6% vertical clear space. For responsive UI, use intrinsic square image boxes rather than manually trimming the transparent edges.

**Brand mark:** The simplified SVG icon is a purpose-built flat icon derived from the same one-eyed helmet silhouette; it is **not** a traced/vectorized version of the detailed 3D source. At launcher/icon sizes the simpler mark is more legible. Use `glancelot-app-dark.svg`/`glancelot-app-light.svg` for scalable branding. SVG may not be appropriate for all native launchers; raster PNG sizes are included.

**Icon specifics:** The `favicon.ico` contains multiple sizes. iOS/WebKit and some desktop tools may mask corners differently, so production app icons deliberately fill the square and leave OS rounding to the platform. The `maskable` variants scale the graphic inward for launcher masking. Do not use images with pre-rounded corner masks for the actual application manifest.

**License/provenance:** The detailed mascot artwork is provided by the user. No third-party artwork or stock assets were introduced. The newly drawn UI glyphs and one-eye emblem were generated for this package; no claims are made about trademarks or third-party likeness clearance.

## Rebuilding

Run `python build_asset_pack.py --source-dir ./sources --output-dir .` from the pack root. Requires Pillow and CairoSVG. This recreates derivatives, manifest, contact sheets, and logs without modifying `sources/`.
