// Copyright (c) 2011, Christian Rorvik
// Distributed under the Simplified BSD License (See accompanying file LICENSE.txt)

#ifndef CRUNCH_BENCHMARKING_RESULT_TABLE_DESCRIPTOR_HPP
#define CRUNCH_BENCHMARKING_RESULT_TABLE_DESCRIPTOR_HPP

#include "crunch/base/enum_class.hpp"

#include <cstdint>
#include <vector>

namespace Crunch { namespace Benchmarking {

CRUNCH_ENUM_CLASS ColumnType : int
{
    Float64,
    Int32,
    String
};

class ResultTableDescriptor
{
public:
    ResultTableDescriptor(const char* name, std::uint32_t version)
        : mName(name)
        , mVersion(version)
    {}

    char const* GetName() const
    {
        return mName;
    }

    std::uint32_t GetVersion() const
    {
        return mVersion;
    }

    void AddColumn(char const* name, ColumnType type)
    {
        ColumnDescriptor const desc = { name, type };
        mColumns.push_back(desc);
    }

    std::size_t GetNumColumns() const
    {
        return mColumns.size();
    }

    char const* GetColumnName(std::size_t index) const
    {
        return mColumns[index].name;
    }

    ColumnType GetColumnType(std::size_t index) const
    {
        return mColumns[index].type;
    }

private:
    struct ColumnDescriptor
    {
        char const* name;
        ColumnType type;
    };

    char const* mName;
    std::uint32_t mVersion;
    std::vector<ColumnDescriptor> mColumns;
};

}}

#endif
