//
//

#pragma once

namespace mcp {

// Initiates connection and negotiates protocol capabilities.
// https://spec.modelcontextprotocol.io/specification/2024-11-05/basic/lifecycle/#initialization
inline auto kMethodInitialize = "initialize";

// Verifies connection liveness between client and server.
// https://spec.modelcontextprotocol.io/specification/2024-11-05/basic/utilities/ping/
inline auto kMethodPing = "ping";

// Lists all available server resources.
// https://spec.modelcontextprotocol.io/specification/2024-11-05/server/resources/
inline auto kMethodResourcesList = "resources/list";

// Provides URI templates for constructing resource URIs.
// https://spec.modelcontextprotocol.io/specification/2024-11-05/server/resources/
inline auto kMethodResourcesTemplatesList = "resources/templates/list";

// Retrieves content of a specific resource by URI.
// https://spec.modelcontextprotocol.io/specification/2024-11-05/server/resources/
inline auto kMethodResourcesRead = "resources/read";

// Lists all available prompt templates.
// https://spec.modelcontextprotocol.io/specification/2024-11-05/server/prompts/
inline auto kMethodPromptsList = "prompts/list";

// Retrieves a specific prompt template with filled parameters.
// https://spec.modelcontextprotocol.io/specification/2024-11-05/server/prompts/
inline auto kMethodPromptsGet = "prompts/get";

// Lists all available executable tools.
// https://spec.modelcontextprotocol.io/specification/2024-11-05/server/tools/
inline auto kMethodToolsList = "tools/list";

// Invokes a specific tool with provided parameters.
// https://spec.modelcontextprotocol.io/specification/2024-11-05/server/tools/
inline auto kMethodToolsCall = "tools/call";

}  // namespace mcp
