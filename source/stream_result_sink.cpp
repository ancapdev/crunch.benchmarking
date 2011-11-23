// Copyright (c) 2011, Christian Rorvik
// Distributed under the Simplified BSD License (See accompanying file LICENSE.txt)

#include "crunch/benchmarking/stream_result_sink.hpp"
#include "crunch/base/assert.hpp"

#include <algorithm>
#include <cstring>
#include <iomanip>
#include <ostream>

namespace Crunch { namespace Benchmarking {

StreamResultSink::StreamResultSink(std::ostream& stream, bool showProgress)
    : mStream(stream)
    , mShowProgress(showProgress)
{}

void StreamResultSink::BeginTable(Benchmarking::ResultTableDescriptor const& descriptor)
{
    mCurrentDescriptor.reset(new ResultTableDescriptor(descriptor));
    mStream << std::endl;
    mStream << "  " << descriptor.GetName() << " v" << descriptor.GetVersion();
    if (mShowProgress)
        mStream << ": Running..";
}

void StreamResultSink::EndTable()
{
    std::size_t const numColumns = mCurrentDescriptor->GetNumColumns();
    std::vector<std::size_t> columnWidths;

    for (std::size_t i = 0; i < numColumns; ++i)
        columnWidths.push_back(std::strlen(mCurrentDescriptor->GetColumnName(i)));

    std::for_each(mRows.begin(), mRows.end(), [&] (Row const& r) {
        CRUNCH_ASSERT(r.size() == numColumns);
        for (std::size_t i = 0; i < numColumns; ++i)
            columnWidths[i] = std::max(columnWidths[i], r[i].first.size());
    });

    if (mShowProgress)
        mStream << "done!";
    mStream << std::endl;

    auto const addSeparator = [&] {
        mStream << "+";
        mStream << std::setfill('-');
        for (std::size_t i = 0; i < numColumns; ++i)
            mStream << std::setw(columnWidths[i] + 3) << "+";
        mStream << std::endl;
        mStream << std::setfill(' ');
    };

    addSeparator();
    
    mStream << "| ";
    mStream << std::left;
    for (std::size_t i = 0; i < numColumns; ++i)
        mStream << std::setw(columnWidths[i]) << mCurrentDescriptor->GetColumnName(i) << " | ";
    mStream << std::endl;
    mStream << std::right;

    addSeparator();

    std::for_each(mRows.begin(), mRows.end(), [&] (Row const& r) {
        mStream << "| ";
        for (std::size_t i = 0; i < numColumns; ++i)
        {
            if (r[i].second)
                mStream << std::left;
            else
                mStream << std::right;
            mStream << std::setw(columnWidths[i]) << r[i].first << " | ";
        }
        mStream << std::endl;
        mStream << std::right;
    });

    addSeparator();
    mStream << std::endl;

    mRows.clear();
    mCurrentDescriptor.reset();
}

void StreamResultSink::BeginRow()
{
    if (mShowProgress)
        mStream << ".";

    mRows.push_back(Row());
}

void StreamResultSink::EndRow()
{
}

void StreamResultSink::Add(double value)
{
    mTempStream.str("");
    mTempStream << value;
    mRows.back().push_back(std::make_pair(mTempStream.str(), false));
}

void StreamResultSink::Add(std::int32_t value)
{
    mTempStream.str("");
    mTempStream << value;
    mRows.back().push_back(std::make_pair(mTempStream.str(), false));
}

void StreamResultSink::Add(const std::string& value)
{
    mRows.back().push_back(std::make_pair(value, true));
}


}}
