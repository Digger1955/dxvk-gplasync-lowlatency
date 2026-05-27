#pragma once

#include "../util/config/config.h"

#include "../vulkan/vulkan_loader.h"

namespace dxvk {

  struct DxvkOptions {
    DxvkOptions() { }
    DxvkOptions(const Config& config);

    /// Enable debug utils
    bool enableDebugUtils = false;

    /// Enable state cache
    bool enableStateCache = true;

    /// Enable memory defragmentation
    Tristate enableMemoryDefrag = Tristate::Auto;

    /// Number of compiler threads
    /// when using the state cache
    int32_t numCompilerThreads = 0;

    /// Enable graphics pipeline library
    Tristate enableGraphicsPipelineLibrary = Tristate::False;

    /// Enable descriptor buffer
    Tristate enableDescriptorBuffer = Tristate::Auto;

    /// Enables pipeline lifetime tracking
    Tristate trackPipelineLifetime = Tristate::Auto;

    /// Enable async pipelines
    bool enableAsync = true;
    
    // Enable state cache with gpl and fixes for async
    bool gplAsyncCache;

    /// dyasync-style stride-normalised stand-in (default: true).
    ///
    /// When a live draw call misses findInstance() because its ilBinding strides
    /// differ from the stride-0 entries stored by the state cache (PR #81 zeroes
    /// strides on write), this option enables the following behaviour:
    ///
    ///   1. Zero the live strides to produce a normalised state.
    ///   2. Call findInstance(normalisedState).
    ///   3. If a compiled instance exists, return its handle immediately as a
    ///      temporary stand-in (geometry is always visible, possible 1-frame
    ///      visual difference -- same trade-off as dyasync in DXVK-Sarek).
    ///   4. Queue the exact live-stride variant at High priority.
    ///   5. When compilation finishes, future calls return the exact pipeline.
    ///
    /// Equivalent to dyasync FallbackMap in pythonlover02/DXVK-Sarek
    /// (old-main-dyasync), adapted to the GPLALL stride-normalisation axis.
    bool dyasyncStrideFallback;

    /// Shader-related options
    Tristate useRawSsbo = Tristate::Auto;

    /// HUD elements
    std::string hud;

    /// Forces swap chain into MAILBOX (if true)
    /// or FIFO_RELAXED (if false) present mode
    Tristate tearFree = Tristate::Auto;

    /// Enables latency sleep
    /// Defaults to false in this build to activate the FramePacer,
    /// especially for the case when the game doesn't support Reflex
    Tristate latencySleep = Tristate::False;

    /// Latency tolerance, in microseconds
    int32_t latencyTolerance = 0u;

    /// Disable VK_NV_low_latency2. This extension
    /// appears to be all sorts of broken on 32-bit.
    Tristate disableNvLowLatency2 = Tristate::Auto;

    // Hides integrated GPUs if dedicated GPUs are
    // present. May be necessary for some games that
    // incorrectly assume monitor layouts.
    bool hideIntegratedGraphics = false;

    /// Clears all mapped memory to zero.
    bool zeroMappedMemory = false;

    /// Allows full-screen exclusive mode on Windows
    bool allowFse = false;

     /// Frame pacing
    std::string framePace;

    /// A value in microseconds to fine-tune the low-latency frame pacing.
    /// Positive values make a frame begin later which might improve responsiveness.
    /// Negative values make a frame begin earlier which might improve fps.
    int32_t lowLatencyOffset;

    /// Determines whether a frame is allowed to begin before finishing processing
    /// the cpu-part of the previous one, when low-latency frame pacing is used.
    bool lowLatencyAllowCpuFramesOverlap;

    /// Whether to enable tiler optimizations
    Tristate tilerMode = Tristate::Auto;

    /// Overrides memory budget for DXVK
    VkDeviceSize maxMemoryBudget = 0u;

    // Device name
    std::string deviceFilter;
  };

}
