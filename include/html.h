/******************************************************************************
 *    ______ ____ _____     ______               _
 *   / ____//  _// ___/    / ____/____   ____ _ (_)____   ___
 *  / / __  / /  \__ \    / __/  / __ \ / __ `// // __ \ / _ \
 * / /_/ /_/ /  ___/ /   / /___ / / / // /_/ // // / / //  __/
 * \____//___/ /____/   /_____//_/ /_/ \__, //_//_/ /_/ \___/
 *                                    /____/
 * @file html.h
 * @brief
 * @details
 * @date 2023-06-19
 * @author
 *
 ******************************************************************************/

#pragma once

#include "flags.h"
#include "stringhelp.h"

/// @brief 封装Google-Gumbo库
namespace Lite {
namespace Utility {

/// @brief html节点类型
enum class GsHtmlNodeType : int
{
    eNODE_DOCUMENT,
    eNODE_ELEMENT,
    eNODE_TEXT,
    eNODE_CDATA,
    eNODE_COMMENT,
    eNODE_WHITESPACE,
    eNODE_TEMPLATE
};

/// @brief html中Tag类型
enum class GsHtmlTag : int
{
    eTAG_HTML,
    eTAG_HEAD,
    eTAG_TITLE,
    eTAG_BASE,
    eTAG_LINK,
    eTAG_META,
    eTAG_STYLE,
    eTAG_SCRIPT,
    eTAG_NOSCRIPT,
    eTAG_TEMPLATE,
    eTAG_BODY,
    eTAG_ARTICLE,
    eTAG_SECTION,
    eTAG_NAV,
    eTAG_ASIDE,
    eTAG_H1,
    eTAG_H2,
    eTAG_H3,
    eTAG_H4,
    eTAG_H5,
    eTAG_H6,
    eTAG_HGROUP,
    eTAG_HEADER,
    eTAG_FOOTER,
    eTAG_ADDRESS,
    eTAG_P,
    eTAG_HR,
    eTAG_PRE,
    eTAG_BLOCKQUOTE,
    eTAG_OL,
    eTAG_UL,
    eTAG_LI,
    eTAG_DL,
    eTAG_DT,
    eTAG_DD,
    eTAG_FIGURE,
    eTAG_FIGCAPTION,
    eTAG_MAIN,
    eTAG_DIV,
    eTAG_A,
    eTAG_EM,
    eTAG_STRONG,
    eTAG_SMALL,
    eTAG_S,
    eTAG_CITE,
    eTAG_Q,
    eTAG_DFN,
    eTAG_ABBR,
    eTAG_DATA,
    eTAG_TIME,
    eTAG_CODE,
    eTAG_VAR,
    eTAG_SAMP,
    eTAG_KBD,
    eTAG_SUB,
    eTAG_SUP,
    eTAG_I,
    eTAG_B,
    eTAG_U,
    eTAG_MARK,
    eTAG_RUBY,
    eTAG_RT,
    eTAG_RP,
    eTAG_BDI,
    eTAG_BDO,
    eTAG_SPAN,
    eTAG_BR,
    eTAG_WBR,
    eTAG_INS,
    eTAG_DEL,
    eTAG_IMAGE,
    eTAG_IMG,
    eTAG_IFRAME,
    eTAG_EMBED,
    eTAG_OBJECT,
    eTAG_PARAM,
    eTAG_VIDEO,
    eTAG_AUDIO,
    eTAG_SOURCE,
    eTAG_TRACK,
    eTAG_CANVAS,
    eTAG_MAP,
    eTAG_AREA,
    eTAG_MATH,
    eTAG_MI,
    eTAG_MO,
    eTAG_MN,
    eTAG_MS,
    eTAG_MTEXT,
    eTAG_MGLYPH,
    eTAG_MALIGNMARK,
    eTAG_ANNOTATION_XML,
    eTAG_SVG,
    eTAG_FOREIGNOBJECT,
    eTAG_DESC,
    eTAG_TABLE,
    eTAG_CAPTION,
    eTAG_COLGROUP,
    eTAG_COL,
    eTAG_TBODY,
    eTAG_THEAD,
    eTAG_TFOOT,
    eTAG_TR,
    eTAG_TD,
    eTAG_TH,
    eTAG_FORM,
    eTAG_FIELDSET,
    eTAG_LEGEND,
    eTAG_LABEL,
    eTAG_INPUT,
    eTAG_BUTTON,
    eTAG_SELECT,
    eTAG_DATALIST,
    eTAG_OPTGROUP,
    eTAG_OPTION,
    eTAG_TEXTAREA,
    eTAG_KEYGEN,
    eTAG_OUTPUT,
    eTAG_PROGRESS,
    eTAG_METER,
    eTAG_DETAILS,
    eTAG_SUMMARY,
    eTAG_MENU,
    eTAG_MENUITEM,
    eTAG_APPLET,
    eTAG_ACRONYM,
    eTAG_BGSOUND,
    eTAG_DIR,
    eTAG_FRAME,
    eTAG_FRAMESET,
    eTAG_NOFRAMES,
    eTAG_ISINDEX,
    eTAG_LISTING,
    eTAG_XMP,
    eTAG_NEXTID,
    eTAG_NOEMBED,
    eTAG_PLAINTEXT,
    eTAG_RB,
    eTAG_STRIKE,
    eTAG_BASEFONT,
    eTAG_BIG,
    eTAG_BLINK,
    eTAG_CENTER,
    eTAG_FONT,
    eTAG_MARQUEE,
    eTAG_MULTICOL,
    eTAG_NOBR,
    eTAG_SPACER,
    eTAG_TT,
    eTAG_RTC,
};


/// @brief Html属性空间
/// @details HTML包括对属性上的XLink、XML和XMLNS命名空间的特殊处理。其他所有内容都在通用的“NONE”命名空间中
enum class GsHtmlAttributeNamespace
{
    eATTR_NAMESPACE_NONE,
    eATTR_NAMESPACE_XLINK,
    eATTR_NAMESPACE_XML,
    eATTR_NAMESPACE_XMLNS,
};

/// @brief Html解析标识
enum class GsHtmlParserFlag
{
    /// @brief 一个正常的节点-开始和结束标记都出现在源中，没有任何内容被重新安排
    eINSERTION_NORMAL = 0,
    /// @brief 解析程序插入的一个节点，以实现某种隐含的插入规则
    eINSERTION_BY_PARSER = 1 << 0,
    /// @brief 指示此节点的结束标记未出现在文档源中的标志
    eINSERTION_IMPLICIT_END_TAG = 1 << 1,
    /// @brief 插入的节点的标志，因为它们的存在由其他标记暗示，例如<html>、<head>、<body>、<tbody>
    eINSERTION_IMPLIED = 1 << 3,
    /// @brief 节点的标志，这些节点是从其等效的结束标记转换而来的
    eINSERTION_CONVERTED_FROM_END_TAG = 1 << 4,
    /// @brief 从＜isindex＞标记的解析转换而来的节点的标志。
    eINSERTION_FROM_ISINDEX = 1 << 5,
    /// @brief 重写为＜img＞的＜image＞标记的标志
    eINSERTION_FROM_IMAGE = 1 << 6,
    /// @brief 作为活动格式化元素重建结果而克隆的节点的标志
    eINSERTION_RECONSTRUCTED_FORMATTING_ELEMENT = 1 << 7,
    /// @brief 采用代理算法克隆的节点的标志
    eINSERTION_ADOPTION_AGENCY_CLONED = 1 << 8,
    /// @brief 采用代理算法移动的节点的标志
    eINSERTION_ADOPTION_AGENCY_MOVED = 1 << 9,
    /// @brief 表中已被寄养为父级的节点的标志
    eINSERTION_FOSTER_PARENTED = 1 << 10,
};
GS_DECLARE_FLAGS(GsHtmlParserFlags, GsHtmlParserFlag)


/// @brief Html解析的空间
enum class GsHtmlNamespace
{
    /// @brief 以Html形式解析
    eNAMESPACE_HTML,
    /// @brief 以svg形式解析
    eNAMESPACE_SVG,
    /// @brief 以Mathml形式解析
    eNAMESPACE_MATHML,
};


/// @brief 原始文本缓冲区中的字符位置
struct GsHtmlPosition
{
    /// @brief 行
    unsigned int Line = 0;
    /// @brief 列
    unsigned int Column = 0;
    /// @brief 偏移量
    unsigned int Offset = 0;
};

struct GsHtmlAttribute
{
    GsHtmlAttributeNamespace AttrNamespace;
    GsString strName;
    GsString strValue;
    GsHtmlPosition NameStartPosition;
    GsHtmlPosition NameEndPosition;
    GsHtmlPosition ValueStartPosition;
    GsHtmlPosition ValueEndPosition;
};

struct GsHtmlText
{
    GsString Text;
    GsHtmlPosition StartPosition;
};


class GsHtmlNode
{
};


class GsHtmlDocument
{
public:
    GsHtmlNode *RootNode();
};


}// namespace Utility
}// namespace Lite
