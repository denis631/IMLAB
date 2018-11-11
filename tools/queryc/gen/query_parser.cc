// A Bison parser, made by GNU Bison 3.0.5.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.

#line 37 "/Users/denis.g/Developer/Databases/InMemoryDB/tools/queryc/gen/query_parser.cc" // lalr1.cc:406

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "query_parser.h"

// User implementation prologue.

#line 51 "/Users/denis.g/Developer/Databases/InMemoryDB/tools/queryc/gen/query_parser.cc" // lalr1.cc:414
// Unqualified %code blocks.
#line 39 "/Users/denis.g/Developer/Databases/InMemoryDB/tools/queryc/query_parser.y" // lalr1.cc:415

imlab::QueryParser::symbol_type yylex(imlab::QueryParseContext& qc);

#line 57 "/Users/denis.g/Developer/Databases/InMemoryDB/tools/queryc/gen/query_parser.cc" // lalr1.cc:415


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 12 "/Users/denis.g/Developer/Databases/InMemoryDB/tools/queryc/query_parser.y" // lalr1.cc:481
namespace  imlab  {
#line 143 "/Users/denis.g/Developer/Databases/InMemoryDB/tools/queryc/gen/query_parser.cc" // lalr1.cc:481

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  QueryParser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  QueryParser::QueryParser (imlab::QueryParseContext &qc_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      qc (qc_yyarg)
  {}

  QueryParser::~QueryParser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  QueryParser::by_state::by_state ()
    : state (empty_state)
  {}

  QueryParser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  void
  QueryParser::by_state::clear ()
  {
    state = empty_state;
  }

  void
  QueryParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  QueryParser::by_state::by_state (state_type s)
    : state (s)
  {}

  QueryParser::symbol_number_type
  QueryParser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  QueryParser::stack_symbol_type::stack_symbol_type ()
  {}

  QueryParser::stack_symbol_type::stack_symbol_type (const stack_symbol_type& that)
    : super_type (that.state, that.location)
  {
    switch (that.type_get ())
    {
      case 3: // "integer_value"
        value.copy< int > (that.value);
        break;

      case 20: // predicate
        value.copy< std::pair<std::string, std::string> > (that.value);
        break;

      case 4: // "identifier"
      case 21: // constant
        value.copy< std::string > (that.value);
        break;

      case 19: // predicate_list
        value.copy< std::vector<std::pair<std::string, std::string>> > (that.value);
        break;

      case 16: // attribute_list
      case 17: // table_list
      case 18: // identifier_list
        value.copy< std::vector<std::string> > (that.value);
        break;

      default:
        break;
    }

  }

  QueryParser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
    switch (that.type_get ())
    {
      case 3: // "integer_value"
        value.move< int > (that.value);
        break;

      case 20: // predicate
        value.move< std::pair<std::string, std::string> > (that.value);
        break;

      case 4: // "identifier"
      case 21: // constant
        value.move< std::string > (that.value);
        break;

      case 19: // predicate_list
        value.move< std::vector<std::pair<std::string, std::string>> > (that.value);
        break;

      case 16: // attribute_list
      case 17: // table_list
      case 18: // identifier_list
        value.move< std::vector<std::string> > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  QueryParser::stack_symbol_type&
  QueryParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 3: // "integer_value"
        value.copy< int > (that.value);
        break;

      case 20: // predicate
        value.copy< std::pair<std::string, std::string> > (that.value);
        break;

      case 4: // "identifier"
      case 21: // constant
        value.copy< std::string > (that.value);
        break;

      case 19: // predicate_list
        value.copy< std::vector<std::pair<std::string, std::string>> > (that.value);
        break;

      case 16: // attribute_list
      case 17: // table_list
      case 18: // identifier_list
        value.copy< std::vector<std::string> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


  template <typename Base>
  void
  QueryParser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  QueryParser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    switch (yytype)
    {
            case 16: // attribute_list

#line 65 "/Users/denis.g/Developer/Databases/InMemoryDB/tools/queryc/query_parser.y" // lalr1.cc:635
        { for(int i = 0; i < yysym.value.template as< std::vector<std::string> > ().size(); ++i) { yyoutput << ((i > 0) ? ", " : "") << yysym.value.template as< std::vector<std::string> > ()[i]; }}
#line 379 "/Users/denis.g/Developer/Databases/InMemoryDB/tools/queryc/gen/query_parser.cc" // lalr1.cc:635
        break;

      case 17: // table_list

#line 65 "/Users/denis.g/Developer/Databases/InMemoryDB/tools/queryc/query_parser.y" // lalr1.cc:635
        { for(int i = 0; i < yysym.value.template as< std::vector<std::string> > ().size(); ++i) { yyoutput << ((i > 0) ? ", " : "") << yysym.value.template as< std::vector<std::string> > ()[i]; }}
#line 386 "/Users/denis.g/Developer/Databases/InMemoryDB/tools/queryc/gen/query_parser.cc" // lalr1.cc:635
        break;

      case 18: // identifier_list

#line 65 "/Users/denis.g/Developer/Databases/InMemoryDB/tools/queryc/query_parser.y" // lalr1.cc:635
        { for(int i = 0; i < yysym.value.template as< std::vector<std::string> > ().size(); ++i) { yyoutput << ((i > 0) ? ", " : "") << yysym.value.template as< std::vector<std::string> > ()[i]; }}
#line 393 "/Users/denis.g/Developer/Databases/InMemoryDB/tools/queryc/gen/query_parser.cc" // lalr1.cc:635
        break;


      default:
        break;
    }
    yyo << ')';
  }
#endif

  void
  QueryParser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  void
  QueryParser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  void
  QueryParser::yypop_ (unsigned n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  QueryParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  QueryParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  QueryParser::debug_level_type
  QueryParser::debug_level () const
  {
    return yydebug_;
  }

  void
  QueryParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  QueryParser::state_type
  QueryParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  QueryParser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  QueryParser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  QueryParser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            symbol_type yylookahead (yylex (qc));
            yyla.move (yylookahead);
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case 3: // "integer_value"
        yylhs.value.build< int > ();
        break;

      case 20: // predicate
        yylhs.value.build< std::pair<std::string, std::string> > ();
        break;

      case 4: // "identifier"
      case 21: // constant
        yylhs.value.build< std::string > ();
        break;

      case 19: // predicate_list
        yylhs.value.build< std::vector<std::pair<std::string, std::string>> > ();
        break;

      case 16: // attribute_list
      case 17: // table_list
      case 18: // identifier_list
        yylhs.value.build< std::vector<std::string> > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 73 "/Users/denis.g/Developer/Databases/InMemoryDB/tools/queryc/query_parser.y" // lalr1.cc:856
    { qc.buildAlgebraTree(yystack_[5].value.as< std::vector<std::string> > (), yystack_[3].value.as< std::vector<std::string> > (), yystack_[1].value.as< std::vector<std::pair<std::string, std::string>> > ()); }
#line 634 "/Users/denis.g/Developer/Databases/InMemoryDB/tools/queryc/gen/query_parser.cc" // lalr1.cc:856
    break;

  case 3:
#line 77 "/Users/denis.g/Developer/Databases/InMemoryDB/tools/queryc/query_parser.y" // lalr1.cc:856
    { yylhs.value.as< std::vector<std::string> > () = yystack_[0].value.as< std::vector<std::string> > (); }
#line 640 "/Users/denis.g/Developer/Databases/InMemoryDB/tools/queryc/gen/query_parser.cc" // lalr1.cc:856
    break;

  case 4:
#line 81 "/Users/denis.g/Developer/Databases/InMemoryDB/tools/queryc/query_parser.y" // lalr1.cc:856
    { yylhs.value.as< std::vector<std::string> > () = yystack_[0].value.as< std::vector<std::string> > (); }
#line 646 "/Users/denis.g/Developer/Databases/InMemoryDB/tools/queryc/gen/query_parser.cc" // lalr1.cc:856
    break;

  case 5:
#line 85 "/Users/denis.g/Developer/Databases/InMemoryDB/tools/queryc/query_parser.y" // lalr1.cc:856
    { yystack_[2].value.as< std::vector<std::string> > ().push_back(yystack_[0].value.as< std::string > ()); std::swap(yylhs.value.as< std::vector<std::string> > (), yystack_[2].value.as< std::vector<std::string> > ()); }
#line 652 "/Users/denis.g/Developer/Databases/InMemoryDB/tools/queryc/gen/query_parser.cc" // lalr1.cc:856
    break;

  case 6:
#line 86 "/Users/denis.g/Developer/Databases/InMemoryDB/tools/queryc/query_parser.y" // lalr1.cc:856
    { yylhs.value.as< std::vector<std::string> > () = std::vector<std::string>{yystack_[0].value.as< std::string > ()};   }
#line 658 "/Users/denis.g/Developer/Databases/InMemoryDB/tools/queryc/gen/query_parser.cc" // lalr1.cc:856
    break;

  case 7:
#line 90 "/Users/denis.g/Developer/Databases/InMemoryDB/tools/queryc/query_parser.y" // lalr1.cc:856
    { yystack_[2].value.as< std::vector<std::pair<std::string, std::string>> > ().push_back(yystack_[0].value.as< std::pair<std::string, std::string> > ()); std::swap(yylhs.value.as< std::vector<std::pair<std::string, std::string>> > (), yystack_[2].value.as< std::vector<std::pair<std::string, std::string>> > ()); }
#line 664 "/Users/denis.g/Developer/Databases/InMemoryDB/tools/queryc/gen/query_parser.cc" // lalr1.cc:856
    break;

  case 8:
#line 91 "/Users/denis.g/Developer/Databases/InMemoryDB/tools/queryc/query_parser.y" // lalr1.cc:856
    { yylhs.value.as< std::vector<std::pair<std::string, std::string>> > () = std::vector<std::pair<std::string, std::string>>{yystack_[0].value.as< std::pair<std::string, std::string> > ()}; }
#line 670 "/Users/denis.g/Developer/Databases/InMemoryDB/tools/queryc/gen/query_parser.cc" // lalr1.cc:856
    break;

  case 9:
#line 92 "/Users/denis.g/Developer/Databases/InMemoryDB/tools/queryc/query_parser.y" // lalr1.cc:856
    { yylhs.value.as< std::vector<std::pair<std::string, std::string>> > () = std::vector<std::pair<std::string, std::string>>();   }
#line 676 "/Users/denis.g/Developer/Databases/InMemoryDB/tools/queryc/gen/query_parser.cc" // lalr1.cc:856
    break;

  case 10:
#line 96 "/Users/denis.g/Developer/Databases/InMemoryDB/tools/queryc/query_parser.y" // lalr1.cc:856
    { yylhs.value.as< std::pair<std::string, std::string> > () = std::pair<std::string, std::string>{yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ()}; }
#line 682 "/Users/denis.g/Developer/Databases/InMemoryDB/tools/queryc/gen/query_parser.cc" // lalr1.cc:856
    break;

  case 11:
#line 100 "/Users/denis.g/Developer/Databases/InMemoryDB/tools/queryc/query_parser.y" // lalr1.cc:856
    { yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > (); }
#line 688 "/Users/denis.g/Developer/Databases/InMemoryDB/tools/queryc/gen/query_parser.cc" // lalr1.cc:856
    break;

  case 12:
#line 101 "/Users/denis.g/Developer/Databases/InMemoryDB/tools/queryc/query_parser.y" // lalr1.cc:856
    { yylhs.value.as< std::string > () = std::to_string(yystack_[0].value.as< int > ());; }
#line 694 "/Users/denis.g/Developer/Databases/InMemoryDB/tools/queryc/gen/query_parser.cc" // lalr1.cc:856
    break;

  case 13:
#line 102 "/Users/denis.g/Developer/Databases/InMemoryDB/tools/queryc/query_parser.y" // lalr1.cc:856
    {
                                            std::ostringstream stringStream;
                                            stringStream << "\"" << yystack_[1].value.as< std::string > () << "\"";
                                            yylhs.value.as< std::string > () = stringStream.str();
                                          }
#line 704 "/Users/denis.g/Developer/Databases/InMemoryDB/tools/queryc/gen/query_parser.cc" // lalr1.cc:856
    break;


#line 708 "/Users/denis.g/Developer/Databases/InMemoryDB/tools/queryc/gen/query_parser.cc" // lalr1.cc:856
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  QueryParser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  // Generate an error message.
  std::string
  QueryParser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char QueryParser::yypact_ninf_ = -10;

  const signed char QueryParser::yytable_ninf_ = -1;

  const signed char
  QueryParser::yypact_[] =
  {
      -6,    -2,     7,   -10,     0,     3,   -10,    -2,     6,     2,
       3,   -10,     9,     4,    -9,   -10,     1,     9,   -10,   -10,
     -10,    10,   -10,   -10,    11,   -10
  };

  const unsigned char
  QueryParser::yydefact_[] =
  {
       0,     0,     0,     6,     0,     3,     1,     0,     0,     0,
       4,     5,     9,     0,     0,     8,     0,     0,     2,    12,
      11,     0,    10,     7,     0,    13
  };

  const signed char
  QueryParser::yypgoto_[] =
  {
     -10,   -10,   -10,   -10,    12,   -10,     5,   -10
  };

  const signed char
  QueryParser::yydefgoto_[] =
  {
      -1,     2,     4,     9,     5,    14,    15,    22
  };

  const unsigned char
  QueryParser::yytable_[] =
  {
      17,     1,     3,    18,    19,    20,    21,     6,     7,     8,
      11,     0,    12,    13,    24,    16,    25,     0,     0,    10,
       0,     0,    23
  };

  const signed char
  QueryParser::yycheck_[] =
  {
       9,     7,     4,    12,     3,     4,     5,     0,     8,     6,
       4,    -1,    10,     4,     4,    11,     5,    -1,    -1,     7,
      -1,    -1,    17
  };

  const unsigned char
  QueryParser::yystos_[] =
  {
       0,     7,    15,     4,    16,    18,     0,     8,     6,    17,
      18,     4,    10,     4,    19,    20,    11,     9,    12,     3,
       4,     5,    21,    20,     4,     5
  };

  const unsigned char
  QueryParser::yyr1_[] =
  {
       0,    14,    15,    16,    17,    18,    18,    19,    19,    19,
      20,    21,    21,    21
  };

  const unsigned char
  QueryParser::yyr2_[] =
  {
       0,     2,     7,     1,     1,     3,     1,     3,     1,     0,
       3,     1,     1,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const QueryParser::yytname_[] =
  {
  "\"eof\"", "error", "$undefined", "\"integer_value\"", "\"identifier\"",
  "\"single_quote\"", "\"comma\"", "\"select\"", "\"from\"", "\"and\"",
  "\"where\"", "\"equals\"", "\"semicolon\"", "\"integer\"", "$accept",
  "statement", "attribute_list", "table_list", "identifier_list",
  "predicate_list", "predicate", "constant", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned char
  QueryParser::yyrline_[] =
  {
       0,    73,    73,    77,    81,    85,    86,    90,    91,    92,
      96,   100,   101,   102
  };

  // Print the state stack on the debug stream.
  void
  QueryParser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  QueryParser::yy_reduce_print_ (int yyrule)
  {
    unsigned yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


#line 12 "/Users/denis.g/Developer/Databases/InMemoryDB/tools/queryc/query_parser.y" // lalr1.cc:1163
} //  imlab 
#line 1086 "/Users/denis.g/Developer/Databases/InMemoryDB/tools/queryc/gen/query_parser.cc" // lalr1.cc:1163
#line 109 "/Users/denis.g/Developer/Databases/InMemoryDB/tools/queryc/query_parser.y" // lalr1.cc:1164

// ---------------------------------------------------------------------------------------------------
// Define error function
void imlab::QueryParser::error(const location_type& l, const std::string& m) {
    qc.Error(l.begin.line, l.begin.column, m);
}
// ---------------------------------------------------------------------------------------------------

