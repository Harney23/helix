commit a5ab8552c3a014956ff0657cf4a1396897d24fd3
Author: Ebenezer <Oladivine0306@gmail.com>
Date:   Sun Apr 26 00:14:47 2026 -0500

    [sol] Add support for regex search to conhost and Terminal

diff --git a/src/buffer/out/search.h b/src/buffer/out/search.h
index c991eb92..763b5d40 100644
--- a/src/buffer/out/search.h
+++ b/src/buffer/out/search.h
@@ -20,13 +20,23 @@ Revision History:
 #include "textBuffer.hpp"
 #include "../renderer/inc/IRenderData.hpp"
 
+enum class SearchFlag : unsigned int
+{
+    None = 0,
+
+    CaseInsensitive = 1 << 0,
+    RegularExpression = 1 << 1,
+};
+
+DEFINE_ENUM_FLAG_OPERATORS(SearchFlag);
+
 class Search final
 {
 public:
     Search() = default;
 
-    bool IsStale(const Microsoft::Console::Render::IRenderData& renderData, const std::wstring_view& needle, bool caseInsensitive) const noexcept;
-    bool Reset(Microsoft::Console::Render::IRenderData& renderData, const std::wstring_view& needle, bool caseInsensitive, bool reverse);
+    bool IsStale(const Microsoft::Console::Render::IRenderData& renderData, const std::wstring_view& needle, SearchFlag flags) const noexcept;
+    bool Reset(Microsoft::Console::Render::IRenderData& renderData, const std::wstring_view& needle, SearchFlag flags, bool reverse);
 
     void MoveToCurrentSelection();
     void MoveToPoint(til::point anchor) noexcept;
@@ -39,14 +49,16 @@ public:
     const std::vector<til::point_span>& Results() const noexcept;
     std::vector<til::point_span>&& ExtractResults() noexcept;
     ptrdiff_t CurrentMatch() const noexcept;
+    bool IsOk() const noexcept;
 
 private:
     // _renderData is a pointer so that Search() is constexpr default constructable.
     Microsoft::Console::Render::IRenderData* _renderData = nullptr;
     std::wstring _needle;
-    bool _caseInsensitive = false;
+    SearchFlag _flags{};
     uint64_t _lastMutationId = 0;
 
+    bool _ok{ false };
     std::vector<til::point_span> _results;
     ptrdiff_t _index = 0;
     ptrdiff_t _step = 0;
