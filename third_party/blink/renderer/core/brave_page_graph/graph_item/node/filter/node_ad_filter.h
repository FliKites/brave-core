/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_THIRD_PARTY_BLINK_RENDERER_CORE_BRAVE_PAGE_GRAPH_GRAPH_ITEM_NODE_FILTER_NODE_AD_FILTER_H_
#define BRAVE_THIRD_PARTY_BLINK_RENDERER_CORE_BRAVE_PAGE_GRAPH_GRAPH_ITEM_NODE_FILTER_NODE_AD_FILTER_H_

#include <string>

#include "brave/third_party/blink/renderer/core/brave_page_graph/graph_item/node/filter/node_filter.h"
#include "third_party/blink/renderer/platform/wtf/casting.h"

namespace brave_page_graph {

class NodeAdFilter : public NodeFilter {
 public:
  NodeAdFilter(GraphItemContext* context, const std::string& rule);

  ~NodeAdFilter() override;

  const std::string& GetRule() const { return rule_; }

  ItemName GetItemName() const override;
  ItemDesc GetItemDesc() const override;

  void AddGraphMLAttributes(xmlDocPtr doc,
                            xmlNodePtr parent_node) const override;

  bool IsNodeAdFilter() const override;

 private:
  const std::string rule_;
};

}  // namespace brave_page_graph

namespace blink {

template <>
struct DowncastTraits<brave_page_graph::NodeAdFilter> {
  static bool AllowFrom(const brave_page_graph::NodeFilter& filter_node) {
    return filter_node.IsNodeAdFilter();
  }
  static bool AllowFrom(const brave_page_graph::GraphNode& node) {
    return IsA<brave_page_graph::NodeAdFilter>(
        DynamicTo<brave_page_graph::NodeFilter>(node));
  }
  static bool AllowFrom(const brave_page_graph::GraphItem& graph_item) {
    return IsA<brave_page_graph::NodeAdFilter>(
        DynamicTo<brave_page_graph::GraphNode>(graph_item));
  }
};

}  // namespace blink

#endif  // BRAVE_THIRD_PARTY_BLINK_RENDERER_CORE_BRAVE_PAGE_GRAPH_GRAPH_ITEM_NODE_FILTER_NODE_AD_FILTER_H_
