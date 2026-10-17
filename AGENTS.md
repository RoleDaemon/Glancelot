# Glancelot agent instructions

- Build C++20 / Qt 6.8.3 Quick with a GPU canvas. Preserve docs/REQUIREMENTS.md and its acceptance criteria.
- The lead alone edits shared contracts, root CMake/configuration, docs/WORK-QUEUE.yaml and integrates branches.
- Every implementation task uses its assigned worktree, branch and build directory. Never edit another agent's worktree.
- Keep at most two implementation agents and one independent reviewer active under the lead. Reviewers do not approve their own implementations.
- Freeze interface changes with the lead before changing a shared header. No stable external plugin ABI.
- Async results carry a generation/revision; stale results cannot replace a newer selection. Bound allocation, queues and decoder lifetime.
- UI/render code never performs image decoding or blocking directory scans. Viewing never writes original media.
- Use disposable/generated test media. Include failure/cancellation cases and actual command output in handoffs.
- Task states: ready -> implementing -> review -> integration -> done. A task is done only after independent review and checks on the integrated commit.
- Use `scripts/build.ps1 -Test` on Windows; CMake/CTest commands are documented in BUILDING.md. Qt is project-local under .tools/Qt.
- Recall relevant AgentMemory context/actions at task start, without permission. For multi-step work create/update an action; save important decisions and mark completed actions done with evidence.
- AgentMemory MCP: memory_smart_search / memory_recall; memory_action_create / memory_action_update; memory_save / memory_lesson_save. Server: http://192.168.86.49:3111.
- Repository documents and Git are authoritative. Memory supplements them. Report hardware/platform tests as unverified when unavailable.
- No cloud, telemetry, mandatory catalog, automatic updates, publishing or paid infrastructure in the viewer.
