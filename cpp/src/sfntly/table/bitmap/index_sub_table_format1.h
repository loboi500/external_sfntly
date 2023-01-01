/*
 * Copyright 2011 Google Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SFNTLY_CPP_SRC_SFNTLY_TABLE_BITMAP_INDEX_SUBTABLE_FORMAT1_H_
#define SFNTLY_CPP_SRC_SFNTLY_TABLE_BITMAP_INDEX_SUBTABLE_FORMAT1_H_

#include "sfntly/port/java_iterator.h"
#include "sfntly/table/bitmap/index_sub_table.h"

namespace sfntly {
// Format 1 Index Subtable Entry.
class IndexSubTableFormat1 : public IndexSubTable,
                             public RefCounted<IndexSubTableFormat1> {
 public:
  class Builder : public IndexSubTable::Builder,
                  public RefCounted<Builder> {
   public:
    class BitmapGlyphInfoIterator
        : public RefIterator<BitmapGlyphInfo, Builder, IndexSubTable::Builder> {
     public:
      explicit BitmapGlyphInfoIterator(Builder* container);
      virtual ~BitmapGlyphInfoIterator() {}

      virtual bool HasNext();
      CALLER_ATTACH virtual BitmapGlyphInfo* Next();

     private:
      int32_t glyph_id_;
    };

    virtual ~Builder();
    virtual int32_t NumGlyphs();
    virtual int32_t GlyphLength(int32_t glyph_id);
    virtual int32_t GlyphStartOffset(int32_t glyph_id);
    CALLER_ATTACH virtual BitmapGlyphInfoIterator* GetIterator();

    virtual CALLER_ATTACH FontDataTable* SubBuildTable(ReadableFontData* data);
    virtual void SubDataSet();
    virtual int32_t SubDataSizeToSerialize();
    virtual bool SubReadyToSerialize();
    virtual int32_t SubSerialize(WritableFontData* new_data);

    std::vector<int32_t>* OffsetArray();
    void SetOffsetArray(const std::vector<int32_t>& offset_array);
    CALLER_ATTACH BitmapGlyphInfoIter* Iterator();

    static CALLER_ATTACH Builder* CreateBuilder();
    static CALLER_ATTACH Builder* CreateBuilder(ReadableFontData* data,
                                                int32_t index_sub_table_offset,
                                                int32_t first_glyph_index,
                                                int32_t last_glyph_index);
    static CALLER_ATTACH Builder* CreateBuilder(WritableFontData* data,
                                                int32_t index_sub_table_offset,
                                                int32_t first_glyph_index,
                                                int32_t last_glyph_index);

   protected:
    void Revert();

   private:
    Builder();
    Builder(WritableFontData* data,
            int32_t first_glyph_index,
            int32_t last_glyph_index);
    Builder(ReadableFontData* data,
            int32_t first_glyph_index,
            int32_t last_glyph_index);
    std::vector<int32_t>* GetOffsetArray();
    void Initialize(ReadableFontData* data);

    static int32_t DataLength(ReadableFontData* data,
                              int32_t index_sub_table_offset,
                              int32_t first_glyph_index,
                              int32_t last_glyph_index);

    std::vector<int32_t> offset_array_;
  };

  virtual ~IndexSubTableFormat1();

  virtual int32_t NumGlyphs();
  virtual int32_t GlyphStartOffset(int32_t glyph_id);
  virtual int32_t GlyphLength(int32_t glyph_id);

  static int32_t GetDataLength(ReadableFontData* data,
                               int32_t offset,
                               int32_t first,
                               int32_t last);

 private:
  IndexSubTableFormat1(ReadableFontData* data,
                       int32_t first_glyph_index,
                       int32_t last_glyph_index);
  int32_t Loca(int32_t loca_index);

  friend class Builder;
};
typedef Ptr<IndexSubTableFormat1> IndexSubTableFormat1Ptr;
typedef Ptr<IndexSubTableFormat1::Builder> IndexSubTableFormat1BuilderPtr;

}  // namespace sfntly

#endif  // SFNTLY_CPP_SRC_SFNTLY_TABLE_BITMAP_INDEX_SUBTABLE_FORMAT1_H_
