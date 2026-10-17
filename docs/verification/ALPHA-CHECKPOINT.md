# Native alpha checkpoint — October 17, 2026

The current deliverable is an early Windows portable alpha, not the complete v1 roadmap. Source baseline 3b054b4 plus the subsequent independent tests and reviewed repairs recorded in Git.

## Implemented and exercised

- Native Qt 6.8.3/MSVC2022 viewer, separate JPEG/PNG decoder, bounded transfer admission, generation checks, cancellation, asynchronous directory work and command/settings persistence.
- GPU canvas, fit/pan/zoom, loupe/rotation, all-eight EXIF orientation decode, directory navigation and boundary behavior. Original photos are never rewritten while viewing.
- Original supplied app icon and empty-state knight; Slate & Ice uses all twelve supplied light/dark palette roles exactly. Forty local theme families/eighty variants, search/swatches, system/dark/light mode, immediate application and persisted choice.
- Independent review found and drove fixes for stale boundary publication, lost repeated navigation, stale timestamp cache reuse, Windows page-rounded shared memory, QProcess destruction, light-theme primary contrast, Windows settings handle replacement, unknown appearance keys, QML final-property shadowing and minimum-window theme-picker layout.

## Evidence

`scripts/build.ps1 -Test -Package`: four CTest targets passed, zero failures. Final run: navigation 0.74 s, viewer_acceptance 4.20 s, viewport 0.04 s, themes 0.07 s. Independent reviewer execution separately reported acceptance 19/19, viewport 9/9 and themes 9/9 (Qt init/cleanup included in those counts). Viewer acceptance treats running-QProcess destruction warnings as failures.

Ubuntu 24.04 WSL, GCC C++20: integrated navigation tests passed; permission-denial enforcement=1, in-progress cancellation observed=1, directory/cycle/file symlink creation=1. Windows link creation was unavailable and is not claimed verified.

Native timed-window captures exercised Slate & Ice dark/light, theme picker, generated 960x640 PNG and minimum 540x360 window. Screenshot rendering was inspected, including compact-picker repair. Timed hidden launches report no presentation frames before grabWindow; these are rendering smoke checks, not latency/high-refresh qualification.

Portable `dist/Glancelot/bin/glancelot.exe` opens the generated image and picker with Qt removed from PATH and no application stderr. Final minimum-window smoke exits 0. This is same-machine runtime independence, not a fresh-VM installation qualification.

Portable archive: `dist/Glancelot.zip`. SHA256: `8F46673E5A78C2C15A7BAA6A24435819C94751863318DFC07B72A43456BDAE3B`.

## Remaining qualifications and work

- Full Linux GUI package, physical fractional-DPI/color/high-refresh/HDR tests, clean Windows VM and actual presentation timing are unverified.
- Decoder isolation is process separation and memory/timeout policy; complete OS sandbox enforcement remains unfinished. OS filesystem calls cannot always be interrupted by cooperative cancellation.
- Independent acceptance observed one intermittent QTemporaryDir cleanup warning after asynchronous cancellation. The process-destructor warning is fixed; temporary-handle/reaper lifetime remains a hardening follow-up.
- Qt deployment reports missing optional translations; this alpha UI is English only. Brand redistribution terms and complete dependency source/notices are public-release prerequisites; this package is local development output.
- Prefetch optimization, browsing panels/filmstrip/grid, RAW, XMP culling, comparison, archives, motion, full input matrix and HDR remain tracked. The bounded retained image cache is not yet used as a trusted prefetch source because file identity validation must improve first.

Next ready work: a reviewed browsing slice (lazy visible file/thumbnail model and filmstrip), then the remaining scheduler/prefetch and Linux GUI feasibility gates. Keep the user-defined roadmap acceptance criteria unchanged.
