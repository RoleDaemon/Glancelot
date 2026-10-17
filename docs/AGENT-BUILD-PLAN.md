# Agent-led execution

The product baseline is BUILD-PLAN.md and the 87 rows in REQUIREMENTS.md. This document records implementation authority from the user's accepted agent-led plan.

Four slots: lead/integrator; two scoped implementation agents; independent reviewer. Each implementation uses a branch/worktree/build directory. The lead alone changes contracts, shared build configuration and WORK-QUEUE.yaml, and integrates sequentially. Reviewer must not approve their own implementation. All async work has generation/revision validation and memory admission.

Task packet: ID/requirements; outcome; dependencies/base commit; owned files/exclusions; interfaces; acceptance/failure/cancellation/platform cases; verification commands; handoff commit/evidence/limitations. Lifecycle ready -> implementing -> review -> integration -> done. Two failed repairs trigger narrowed investigation, not weakened acceptance.

Waves: (0) toolchain/contracts/fixtures; (1) isolated decode + GPU/SDR/DPI proof; (2) daily viewer alpha; (3) browsing/HUD/RAW; (4) culling/XMP/safe file operations; (5) qualified formats/diagnostics; (6) hardening/release; (7) archives/motion/HDR expansions. Each wave ends with a runnable artifact and evidence. Linux hardware claims remain unverified until measured; WSL/VM only validates corresponding capabilities.

Author tests -> independent review/acceptance -> serial integration -> integrated checks -> done. Your feedback is advisory and not a routine gate. Agents continue ready tasks, preserving evidence of infrastructure blocks. Public publishing, paid services and new external access are separate actions. Forecast from first ten integrated tasks, not agent-count multiplication. Sessions checkpoint work; agents do not promise execution after the session ends.

## Initial contracts and allocation

Frozen headers in include/glancelot establish identity/revisions, commands/navigation, decode/pixel metadata and viewport/display capabilities. Initial source support is JPEG/PNG only; the capability page must report actual delivery instead of the full target inventory.

- Lead: build/dependency/bootstrap scripts, decoder process, ViewerController backend, app entry, documentation, integration.
- Navigation agent: src/core/navigation.cpp and tests/navigation_tests.cpp.
- Canvas agent: src/render/* and ui/Main.qml.
- Independent reviewer: tests/acceptance_tests.cpp and docs/verification/ACCEPTANCE.md, then independent code/behavior review.
