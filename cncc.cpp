// ==============================================================
//
//  Copyright (C) 2003-2004, 2015  Alex Vinokur.
//
//  ------------------------------------------------------------
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//  ------------------------------------------------------------
// 
//  mailto:alex.vinokur@gmail.com
//  https://www.linkedin.com/in/alexvinokur
//
// ==============================================================


// ##############################################################
//
//  SOFTWARE : Print line and byte counts of C/C++ sources
//  FILE     : cncc.cpp
//
//  DESCRIPTION :
//          `cncc' counts the number of code, comment and empty 
//          lines and bytes of C/C++-sources 
//          which have been successfully compiled.
//
#define VERSION_No	"1.4.0"
//
// ##############################################################



#include <cstdlib>
#include <climits>
#include <cassert>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <algorithm>


// --------------
static std::string	CurFilename_Static;

// --------------
typedef unsigned long ulong;

#define  MAX_VALUE(x,y)  ((x) > (y) ? (x) : (y))

#define ASSERTION(x) if (!(x)) \
	{ \
	  std::cerr << "" \
	       << "### "\
	       << PROGRAM_NAME \
	       << " : Version "\
	       << VERSION_No \
	       << " ###"\
	       << std::endl; \
	  std::cerr << "" \
	       << "[" \
	       << __FILE__ \
	       << ", #" \
	       << __LINE__ \
	       << "] " \
	       << "There is some problem with file `" \
	       << CurFilename_Static \
	       << "'." \
	       << std::endl; \
	  std::cerr << "" \
	       << "Has `" \
	       << CurFilename_Static \
	       << "' been successfully compiled?" \
	       << std::endl; \
	  exit(1); \
	}

// --------------
enum ByteModeId 
{ 
  UNDEF_ByteModeId, 
  // ----------------
  LIVING_SPACE_Id, 
  // ----------------
  CPP_BRACKET_Id, 
  CL_BRACKET_Id, 
  CR_BRACKET_Id, 
  COMMENT_Id, 
  // ----------------
  QL_BRACKET_Id, 
  QR_BRACKET_Id, 
  Q_STRING_Id, 
  // ----------------
  LAST_ByteModeId 
};

#define PROGRAM_NAME		"cncc"


#define CPP_BRACKET		"//"
#define CL_BRACKET		"/*"
#define CR_BRACKET		"*/"

#define SINGLE_QUOTE		"\""
#define QL_BRACKET		SINGLE_QUOTE
#define QR_BRACKET		SINGLE_QUOTE

#define BRACKET_SIZE		2
#define QUOTE_SIZE		1

#define	SPACE_VALUE		' '
#define	TAB_VALUE		'\t'
#define	CR_VALUE		'\r'

#define ONE_SLASH		'\\'

#define	PRE_OPTION_SIGN		'-'

#define	SUMMARY_OPTION		 'a'
#define	DETAILED_OPTION1_ROW	 'b'
#define	DETAILED_OPTION2_ROW	 'c'
#define	DETAILED_OPTION3_ROW_COL 'd'
#define	HELP_OPTION		 'h'
#define	VERSION_OPTION		 'v'

#define ROW_NO_SIZE		7
#define FIELD_NO_SIZE		7

#define LINES_TXT0		"Lines" 
#define BYTES_TXT0		"Chars" 

#define CODE_ONLY_TXT1		"Code Only" 
#define CODE_COMMENT_TXT1	"Code+Comment" 
#define COMMENT_ONLY_TXT1	"Comment Only"
#define EMPTY_TXT1		"Empty"
#define TOTAL_TXT1		"* Total"

#define TXT1_SIZE		13


#define CODE_TXT2		" code" 
#define CODE_STRING_TXT2	" code (std::string)" 
#define COMMENT_TXT2		" comment"
#define COMMENT_BLANK_TXT2	" comment (blank)"
#define EMPTY_TXT2		" blank"

#define TXT2_SIZE		10



#define DELIM1			"|"
#define DELIM2			":"


#define PURIFIED_SUFFIX2	"i2"
#define PURIFIED_SUFFIX3	"i3"

#define PERCENT_FACTOR		100.0
#define PERCENT_SIGN		" %"
#define PERCENT_100		"100"

#define NONE_TXT		"None"


//=====================
template <typename T>
std::string to_str (const T& val_i)
{
std::ostringstream oss;
  oss << val_i;
  return oss.str();
}


//=====================
struct SimpleTable
{
  const std::string              title_;
  const std::vector<ulong>       col_size_;
  const std::string              prefix_;
  std::vector<bool>              align_;
  const bool                total_delim_line_flag_;
  const std::string              outside_delim_;
  const std::string              inside_delim_;
  const ulong               left_space_size_;
  const ulong               right_space_size_;

  std::vector<std::string>            header_str_;
  std::vector<std::string>            row_str_;

  SimpleTable (
	const std::string&        title_i,
	const std::vector<ulong>& col_size_i, 
	const std::string&        prefix_i = "",
	const std::vector<bool>&  align_i = std::vector<bool>(), 
	bool                 total_delim_line_flag_i = false,
	const std::string&        outside_delim_i = "|",
	const std::string&        inside_delim_i = ":"
	);

  ~SimpleTable ();


  void build_header (const std::vector<std::vector<std::string> > header_i);
  void build_row (const std::vector<std::string> row_i);
  void build_empty_row ();

  void print_table () const;
};




// ---------
SimpleTable::SimpleTable (
	const std::string&        title_i,
	const std::vector<ulong>& col_size_i, 
	const std::string&        prefix_i,
	const std::vector<bool>&  align_i, 
	bool                 total_delim_line_flag_i,
	const std::string&        outside_delim_i,
	const std::string&        inside_delim_i
	)
	:
        title_ (title_i),
        col_size_ (col_size_i),
        prefix_ (prefix_i),
	align_ (align_i), 
	total_delim_line_flag_ (total_delim_line_flag_i),
        outside_delim_ (outside_delim_i),
        inside_delim_ (inside_delim_i),
        left_space_size_ (to_str(SPACE_VALUE).size()),
        right_space_size_ (to_str(SPACE_VALUE).size())
{
  assert (!col_size_.empty());

  if (align_.empty()) align_.push_back(true);

  for (ulong k = align_.size(); k < col_size_.size(); k++)
  {
    align_.push_back(false);
  }  

  assert (col_size_.size() == align_.size());

}

// ---------
SimpleTable::~SimpleTable ()
{
  print_table ();
}

// ---------
void SimpleTable::build_header (const std::vector<std::vector<std::string> > header_i)
{

  for (ulong i = 0; i < header_i.size(); i++)
  {
    assert (header_i[i].size () == col_size_.size());

    std::ostringstream oss;
    oss << ""
        << outside_delim_;

    for (ulong k = 0; k < header_i[i].size(); k++)
    {
      assert (header_i[i][k].size () <= col_size_[k]);
      oss << ""
          << SPACE_VALUE
          << std::setw (col_size_[k])
          << (align_[k] ? std::left : std::right)
          << header_i[i][k]
          << SPACE_VALUE;
      if (k < (header_i[i].size() - 1))
      {
        oss << inside_delim_;
      }
      else
      {
        oss << outside_delim_;
      }
    }
    header_str_.push_back(oss.str());
  }

}


// ---------
void SimpleTable::build_empty_row ()
{
std::ostringstream oss;
  oss << ""
      << outside_delim_;
  for (ulong k = 0; k < col_size_.size(); k++)
  {
    oss << ""
        << SPACE_VALUE
        << std::setw (col_size_[k])
        << ""
        << SPACE_VALUE;

    if (k < (col_size_.size() - 1))
    {
      oss << inside_delim_;
    }
    else
    {
      oss << outside_delim_;
    }
  }
  row_str_.push_back(oss.str());

}

// ---------
void SimpleTable::build_row (const std::vector<std::string> row_i)
{
  assert (row_i.size () == col_size_.size());

std::ostringstream oss;
  oss << ""
      << outside_delim_;
  for (ulong k = 0; k < row_i.size(); k++)
  {
    assert (row_i.size () <= col_size_[k]);

    oss << ""
        << SPACE_VALUE
        << std::setw (col_size_[k])
        << (align_[k] ? std::left : std::right)
        << row_i[k]
        << SPACE_VALUE;
    if (k < (row_i.size() - 1))
    {
      oss << inside_delim_;
    }
    else
    {
      oss << outside_delim_;
    }
  }

  row_str_.push_back(oss.str());
}



// ---------
void SimpleTable::print_table () const
{

  std::cout << prefix_ << "--- " << title_ << " ---" << std::endl;

  assert (!header_str_.empty());

  std::cout << prefix_ << std::string (header_str_.back().size(), '=') << std::endl;
  for (ulong k = 0; k < header_str_.size(); k++)
  {
    std::cout << prefix_ << header_str_[k] << std::endl;
  }
  std::cout << prefix_ << outside_delim_ << std::string (header_str_.back().size() - 2, '-') << outside_delim_ << std::endl;

  for (ulong k = 0; k < row_str_.size(); k++)
  {
    if (k == (row_str_.size() - 1))
    {
      if (total_delim_line_flag_)
      {
        std::cout << prefix_ << outside_delim_ << std::string (header_str_.back().size() - 2, '.') << outside_delim_ << std::endl;
      }
    }
    std::cout << prefix_ << row_str_[k] << std::endl;
  }

  std::cout << prefix_ << std::string (header_str_.back().size(), '=') << std::endl;

}



//=====================
struct Couple
{
  ulong        row_no_;
  ulong        field_no_;

  Couple (ulong row_no_i, ulong field_no_i) 
		: 
		row_no_ (row_no_i), 
		field_no_ (field_no_i) 
		{}

  bool get_next(
		const std::vector<std::string>& data_i, 
		ulong&                row_no_o, 
		ulong&                field_no_o
		) const;

};

// ---------
bool Couple::get_next (
		const std::vector<std::string>& data_i, 
		ulong&                row_no_o, 
		ulong&                field_no_o
		) const
{
  ASSERTION (row_no_ < data_i.size());

bool ret_bool = false;

  if (field_no_ == (data_i[row_no_].size() - 1))
  {
    for (ulong k = (row_no_ + 1); k < data_i.size(); k++)
    {
      if (data_i[k].empty()) continue;

      ret_bool = true;

      row_no_o = k;
      field_no_o = 0;

      break;
    }

  }
  else
  {
    ASSERTION (field_no_ < (data_i[row_no_].size() - 1));

    ret_bool = true;

    row_no_o = row_no_;
    field_no_o = field_no_ + 1;
  }

  return ret_bool;
}

// ---------
bool operator< (const Couple& ins1_i, const Couple& ins2_i)
{
  if (ins1_i.row_no_ < ins2_i.row_no_) return true;

  if (
       (ins1_i.row_no_ == ins2_i.row_no_) 
       && 
       (ins1_i.field_no_ < ins2_i.field_no_)
     ) 
  {
    return true;
  }

  return false;
}

// ---------
bool operator<= (const Couple& ins1_i, const Couple& ins2_i)
{
  if (ins1_i < ins2_i) return true;
  if ((ins1_i.row_no_ == ins2_i.row_no_) && (ins1_i.field_no_ == ins2_i.field_no_)) return true;

  return false;
}

// ---------
bool operator== (const Couple& ins1_i, const Couple& ins2_i)
{
  if (ins1_i.row_no_ != ins2_i.row_no_)      return false;
  if (ins1_i.field_no_ != ins2_i.field_no_) return false;

  return true;
}


//=====================
struct Triple
{
  std::vector<ulong>	code_fields_;
  std::vector<ulong>	empty_fields_;
  std::vector<ulong>	comment_fields_;
};

//=====================
class CountCodeLines
{
  private :
    static std::string	        exe_full_name_s;
    static std::string	        exe_basename_s;
    static std::vector<std::string>	filenames_s;
    static ulong		max_filenames_size_s;

    static std::vector<std::string>	actual_options_s;
    static std::map<std::string, std::vector<std::string> > allowed_options_s;

    std::ifstream                fin_;
    const std::string            filename_;
    const bool              open_status_;

    std::vector<std::string>          rows_;
    std::vector<std::string>          modes_;
    std::vector<Triple>          triple_;

    static ulong            all_files_code_only_lines_s;
    static ulong            all_files_code_comment_lines_s;
    static ulong            all_files_comment_only_lines_s;
    static ulong            all_files_empty_lines_s;

    static ulong            all_files_code_fields_s;
    static ulong            all_files_comment_fields_s;
    static ulong            all_files_empty_fields_s;

    bool open_file ();
    void read_file ();

    void assert_check () const;

    void treatment ();

    void init_modes ();
    bool get_first_field (ulong& row_no_o, ulong& field_no_o);
    void sign_modes (ulong row_no_i, ulong field_no_i);

    void mask_modes (
		ulong      row1_i, 
		ulong      field1_i,
		ulong      row2_i, 
		ulong      field2_i,
		ulong      row3_i, 
		ulong      field3_i,
		ByteModeId mode_id_i
		);

    void mask2_modes (
		ulong row_i, 
		ulong field_i
		);


    bool find_token (
		const std::string& token_i, 
		ulong&        row_no_o, 
		ulong&        field_no_o,
		ulong         row_no_i, 
		ulong         field_no_i,
		bool          deny_check_i = false
		) const;


    void prepare_reported_data ();

    void show_report () const;

    void show_summary_report (const std::string& prefix_i) const;
    void show_detailed_report (const std::string& prefix_i) const;

    void create_purified_code () const;


  public :
    CountCodeLines (const std::string& filename_i);
    ~CountCodeLines ();


    bool get_open_status () const { return open_status_;}

    static bool Set_Exe_Filename (const std::string& filename_i);
    static void Init_Allowed_Options ();
    static bool Set_Actual_Options (const std::string& str_i);
    static void Set_Default_Option ();
    static void Show_Help ();
    static void Show_Summary_Report ();
    static void Print_Summary_Report (
			const std::string& center_title_i,
			const std::string& left_title_i,
			ulong         lines_code_only_i,
			ulong         lines_code_comment_i,
			ulong         lines_comment_only_i,
			ulong         lines_empty_i,
			ulong         fields_code_i,
			ulong         fields_comment_i,
			ulong         fields_empty_i
			);
    static void Add_Filename (const std::string& filename_i);
    static const std::vector<std::string>& Get_Filenames ();

};


// ---------
CountCodeLines::CountCodeLines (const std::string& filename_i)
		:
		filename_ (filename_i),
		open_status_ (open_file())
{

  assert_check ();

  assert (!allowed_options_s.empty());

  // ------------------
  assert (!filename_.empty());

  if (!open_status_) return;

  // ------------------
  assert (open_status_);

  read_file ();

  treatment ();

  prepare_reported_data ();
  show_report ();
}


// ---------
CountCodeLines::~CountCodeLines ()
{
  if (fin_.is_open()) fin_.close();
  assert (!fin_.is_open());
}



// ---------
const std::vector<std::string>& CountCodeLines::Get_Filenames ()
{
  return filenames_s;
}

// ---------
void CountCodeLines::Add_Filename (const std::string& filename_i)
{
#define ADDITION_VAL	3
  filenames_s.push_back (filename_i);
  max_filenames_size_s = MAX_VALUE (max_filenames_size_s, filename_i.size() + ADDITION_VAL);
}


// ---------
bool CountCodeLines::Set_Exe_Filename (const std::string& filename_i)
{
  assert (exe_full_name_s.empty());
  exe_full_name_s = filename_i;
  exe_basename_s = exe_full_name_s;


std::string::size_type find_pos;

  find_pos = exe_basename_s.find_last_of ("/\\");
  if (find_pos != std::string::npos) exe_basename_s = exe_basename_s.substr (find_pos + 1);

  find_pos = exe_basename_s.find_last_of (".");
  if (find_pos != std::string::npos) exe_basename_s = exe_basename_s.substr (0, find_pos);


  if (exe_basename_s != PROGRAM_NAME)
  {
    std::cerr << ""
         << std::endl
         << "ERROR : Executable basename must be "
         << "`"
         << PROGRAM_NAME 
         << "'"

         << "; Actual basename is "
         << "`"
         << exe_basename_s
         << "'"

         << ", Actual full name is "
         << "`"
         << exe_full_name_s 
         << "'"

         << "."
         << std::endl;

    return false;
  }

  assert (exe_basename_s == PROGRAM_NAME);
  return true;

}



// ---------
bool CountCodeLines::Set_Actual_Options (const std::string& str_i)
{
  assert (str_i[0] == PRE_OPTION_SIGN);

  if (str_i.size() == 1)
  {
    std::cerr << ""
         << std::endl
         << "WARNING : Option `" 
         << str_i
         << "' is empty and will be ignored." 
         << std::endl;
    return false;
  }

  //assert (str_i.size() > 1);
  
  for (ulong k = 1; k < str_i.size(); k++)
  {
    const std::string cur_option (to_str(str_i[k]));

    if (allowed_options_s.count (cur_option) == 0)
    {
      std::cerr << ""
           << std::endl
           << "WARNING : Option `" 
           << (PRE_OPTION_SIGN + cur_option)
           << "' is illegal and will be ignored." 
           << std::endl;
      continue;
    }

	if (std::count (actual_options_s.begin(), actual_options_s.end(), cur_option) == 0)
    {
      actual_options_s.push_back (cur_option);
    }
  }



  if (count (actual_options_s.begin(), actual_options_s.end(), to_str(HELP_OPTION)))
  { 
    Show_Help();
    return true;
  }

  if (count (actual_options_s.begin(), actual_options_s.end(), to_str(VERSION_OPTION)))
  {
    std::cout << std::endl;
    std::cout << PROGRAM_NAME << " : Version " << VERSION_No << std::endl;

    std::cout << std::endl;
    std::cout << "Copyright (C) 2003-2004, 2015  Alex Vinokur" << std::endl;

    std::cout << "This is free software; see the source for copying conditions." << std::endl;
    std::cout << "There is NO warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE." << std::endl;
    std::cout << std::endl;

    return true;
  }


  if (
       (count (actual_options_s.begin(), actual_options_s.end(), to_str(DETAILED_OPTION2_ROW)))
       &&
       (count (actual_options_s.begin(), actual_options_s.end(), to_str(DETAILED_OPTION3_ROW_COL)))
     )
  {
    std::cerr << ""
         << std::endl
         << "ERROR : Options "
         << "`" 
         << PRE_OPTION_SIGN
         << DETAILED_OPTION2_ROW
         << "'"
         << " and " 
         << "`" 
         << PRE_OPTION_SIGN
         << DETAILED_OPTION3_ROW_COL
         << "'"
         << " are incompatible." 
         << std::endl;

    return true;

  }

  // -------------
  return false;

}

// ---------
void CountCodeLines::Set_Default_Option ()
{
  actual_options_s.push_back (to_str(SUMMARY_OPTION));
}

// ---------
void CountCodeLines::Init_Allowed_Options ()
{
  allowed_options_s [to_str(SUMMARY_OPTION)].push_back ("Print code-line, empty-line and comment-line counts for each FILE.");
  allowed_options_s [to_str(SUMMARY_OPTION)].push_back ("This option is DEFAULT.");

  allowed_options_s [to_str(DETAILED_OPTION1_ROW)].push_back ("Print line-type for each LINE of each FILE.");

  allowed_options_s [to_str(DETAILED_OPTION2_ROW)].push_back ("Print");
  allowed_options_s [to_str(DETAILED_OPTION2_ROW)].push_back ("* line-type");
  allowed_options_s [to_str(DETAILED_OPTION2_ROW)].push_back ("  and");
  allowed_options_s [to_str(DETAILED_OPTION2_ROW)].push_back ("* code-field, empty-field and comment-field counts");
  allowed_options_s [to_str(DETAILED_OPTION2_ROW)].push_back ("for each line of each FILE.");
  allowed_options_s [to_str(DETAILED_OPTION2_ROW)].push_back ("### Note. This option is incompatible with option `" + to_str(PRE_OPTION_SIGN) + to_str(DETAILED_OPTION3_ROW_COL) + "'.");

  allowed_options_s [to_str(DETAILED_OPTION3_ROW_COL)].push_back("Print field-type for each field of each line of each FILE.");
  allowed_options_s [to_str(DETAILED_OPTION3_ROW_COL)].push_back ("### Note. This option is incompatible with option `" + to_str(PRE_OPTION_SIGN) + to_str(DETAILED_OPTION2_ROW) + "'.");

  allowed_options_s [to_str(HELP_OPTION)].push_back("Display this help and exit.");

  allowed_options_s [to_str(VERSION_OPTION)].push_back("Print the version number and exit.");

}



// ---------
void CountCodeLines::Show_Help ()
{
#define PREFIX1	"       "
#define PREFIX2	"              "

  std::cout << std::endl;
  std::cout << std::endl;

  assert (exe_basename_s == PROGRAM_NAME);

  std::cout << ""
       << "NAME"
       << std::endl
       << PREFIX1
       << PROGRAM_NAME
       << " - "
       << "count C/C++ source lines and bytes"
       << std::endl;
  std::cout << std::endl;

  std::cout << ""
       << "SYNOPSIS"
       << std::endl
       << PREFIX1
       << PROGRAM_NAME
       << " [OPTIONS]... [FILE]..." 
       << std::endl;
  std::cout << std::endl;

  std::cout << ""
       << "DESCRIPTION"
       << std::endl
       << PREFIX1 
       << "Count code-lines, empty-lines, comment-lines, "  
       << std::endl
       << PREFIX1 
       << "code-fields, empty-fields, comment-fields of C/C++-sources "
       << std::endl
       << PREFIX1 
       << "which have been successfully compiled." 
       << std::endl;
  std::cout << std::endl;


  std::cout << PREFIX1 << "The program accepts the following options." << std::endl;
  for (std::map<std::string, std::vector<std::string> >::const_iterator pos_iter = allowed_options_s.begin();
       pos_iter != allowed_options_s.end();
       pos_iter++
       )
  {
    std::cout << ""
         << std::endl 
         << PREFIX1
         << "`"
         << PRE_OPTION_SIGN 
         << pos_iter->first
         << "'"
         << std::endl; 

    for (ulong k = 0; k < pos_iter->second.size(); k++)
    {
      std::cout << ""
           << PREFIX2
           << pos_iter->second [k]
           << std::endl;
    }
  }


}


// ---------
void CountCodeLines::assert_check () const
{
  assert (std::string (CPP_BRACKET).size() == BRACKET_SIZE);
  assert (std::string (CL_BRACKET).size()  == BRACKET_SIZE);
  assert (std::string (CR_BRACKET).size()  == BRACKET_SIZE);

  assert (std::string (LINES_TXT0).size() <= ROW_NO_SIZE);
  assert (std::string (BYTES_TXT0).size() <= FIELD_NO_SIZE);

  assert (std::string (CODE_ONLY_TXT1).size()    < TXT1_SIZE);
  assert (std::string (CODE_COMMENT_TXT1).size() < TXT1_SIZE);
  assert (std::string (EMPTY_TXT1).size()        < TXT1_SIZE);
  assert (std::string (COMMENT_ONLY_TXT1).size() < TXT1_SIZE);
  assert (std::string (TOTAL_TXT1).size()        < TXT1_SIZE);

}

// ---------
void CountCodeLines::treatment ()
{

  init_modes ();

ulong row_no;
ulong field_no;
  if (get_first_field (row_no, field_no)) sign_modes(row_no, field_no);

}


// ---------
void CountCodeLines::create_purified_code () const
{
std::string basename (filename_);


std::string::size_type find_pos;
  find_pos = basename.find_last_of ("/\\");
  if (find_pos != std::string::npos) basename = basename.substr (find_pos + 1);

  find_pos = basename.find_last_of (".");
  if (find_pos != std::string::npos)	
  {
    basename = basename.substr (0, find_pos + 2);  // dot + first letter of the suffix
  }
  else
  {
    basename += ".";
  }

const std::string purified_file_name2 (basename + PURIFIED_SUFFIX2);
const std::string purified_file_name3 (basename + PURIFIED_SUFFIX3);

   remove (purified_file_name2.c_str());
   remove (purified_file_name3.c_str());

std::ofstream ofs2 (purified_file_name2.c_str());
std::ofstream ofs3 (purified_file_name3.c_str());


  if (!ofs2)
  {
    std::cerr << ""
         << std::endl
         << "ERROR : Unable to open output file " 
         << purified_file_name2 
         << std::endl;
    return;
  }
  assert (ofs2);
  assert (ofs2.is_open());


  if (!ofs3)
  {
    std::cerr << ""
         << std::endl
         << "ERROR : Unable to open output file " 
         << purified_file_name3 
         << std::endl;
    return;
  }
  assert (ofs3);
  assert (ofs3.is_open());


  ASSERTION (rows_.size() == modes_.size());
  for (ulong row_no = 0; row_no < rows_.size(); row_no++)
  {
    ASSERTION (rows_[row_no].size() == modes_[row_no].size());
    for (ulong field_no = 0;  field_no < rows_[row_no].size(); field_no++)
    {
      ASSERTION (modes_[row_no][field_no] < LAST_ByteModeId);
      switch (modes_[row_no][field_no])
      {
        case LIVING_SPACE_Id :
        case QL_BRACKET_Id :
        case QR_BRACKET_Id : 
        case Q_STRING_Id :
          ofs2 << rows_[row_no][field_no];
          ofs3 << rows_[row_no][field_no];
          break;

        case CPP_BRACKET_Id :
        case CL_BRACKET_Id :
        case CR_BRACKET_Id :
        case COMMENT_Id :
          ofs2 << ' ';
          break;

        default :
          ASSERTION (0);
          break; // unused
      }

    }
    ofs2 << std::endl;
    ofs3 << std::endl;
  }


const std::string pref (max_filenames_size_s, ' ');
std::ostringstream oss;


  oss << "Files purified from comments created";

  std::cout << pref << std::string (oss.str().size(), '-') << std::endl;
  std::cout << pref << oss.str() << std::endl;
  std::cout << pref << "* " << purified_file_name2 << std::endl;
  std::cout << pref << "* " << purified_file_name3 << std::endl;
  std::cout << pref << std::string (oss.str().size(), '-') << std::endl;

  std::cout << std::endl;

}


// ---------
bool CountCodeLines::get_first_field (ulong& row_no_o, ulong& field_no_o)
{
  for (ulong k = 0; k < rows_.size(); k++)
  {
    if (!rows_[k].empty())
    {
      row_no_o   = k;
      field_no_o = 0;
      return true;
    }
  }
  return false;
}

// ---------
void CountCodeLines::sign_modes (ulong row_no_i, ulong field_no_i)
{
  ASSERTION (row_no_i < rows_.size());  
  ASSERTION (field_no_i < rows_[row_no_i].size());  

  // -------------------------
ulong start_selected_row_no; 
ulong start_selected_field_no; 
ulong end_selected_row_no; 
ulong end_selected_field_no; 

ulong cpp_bracket_row_no; 
ulong cpp_bracket_field_no; 

ulong cl_bracket_row_no; 
ulong cl_bracket_field_no; 
ulong cr_bracket_row_no; 
ulong cr_bracket_field_no; 

ulong ql_row_no; 
ulong ql_field_no; 
ulong qr_row_no; 
ulong qr_field_no; 


const bool cpp_bracket_found = find_token (
				CPP_BRACKET, 
				cpp_bracket_row_no, 
				cpp_bracket_field_no,
				row_no_i, 
				field_no_i
				); 

const bool cl_bracket_found = find_token (
				CL_BRACKET, 
				cl_bracket_row_no, 
				cl_bracket_field_no,
				row_no_i, 
				field_no_i
				); 

const bool ql_found = find_token (
				QL_BRACKET, 
				ql_row_no, 
				ql_field_no,
				row_no_i, 
				field_no_i,
				true
				); 


  if (!cpp_bracket_found && !cl_bracket_found & !ql_found) 
  {
    mask2_modes (row_no_i, field_no_i);
    return;
  }

  // -----------------------
  ASSERTION (cpp_bracket_found || cl_bracket_found || ql_found);

const Couple cpp_couple (Couple (cpp_bracket_row_no, cpp_bracket_field_no));
const Couple cl_couple  (Couple (cl_bracket_row_no, cl_bracket_field_no));
const Couple ql_couple  (Couple (ql_row_no, ql_field_no));

std::vector<Couple>  found;

  if (cpp_bracket_found) found.push_back(cpp_couple);
  if (cl_bracket_found)  found.push_back(cl_couple);
  if (ql_found)          found.push_back(ql_couple);

  ASSERTION (!found.empty());

  for (ulong i = 0; i < found.size(); i++)
  {
    for (ulong k = 0; k < found.size(); k++)
    {
      if (i == k) continue;
      ASSERTION (!(found[i] == found[k]));
    }
  }

  sort (found.begin(), found.end());

  // -----------------------

ulong      counter = 0;
ByteModeId mode_id = UNDEF_ByteModeId;

  if (found.front() == cpp_couple)
  {
    counter++;
    mode_id = CPP_BRACKET_Id;

    ASSERTION (cpp_bracket_found);

    start_selected_row_no   = cpp_bracket_row_no; 
    start_selected_field_no = cpp_bracket_field_no; 

    end_selected_row_no     = cpp_bracket_row_no; 
    end_selected_field_no   = modes_[cpp_bracket_row_no].size() - 1; 

  } // if (found.front() == cpp_couple)


  if (found.front() == cl_couple)
  {
    counter++;
    mode_id = CL_BRACKET_Id;

    ASSERTION (cl_bracket_found);

    // -----------------
    bool cr_bracket_found = find_token (
				CR_BRACKET, 
				cr_bracket_row_no, 
				cr_bracket_field_no,
				row_no_i, 
				field_no_i
				); 

    ASSERTION (cr_bracket_found);
    if (
         (cl_bracket_row_no == cr_bracket_row_no)
         &&
         ((cr_bracket_field_no - cl_bracket_field_no) < BRACKET_SIZE)
       )
    {
      cr_bracket_found = find_token (
				CR_BRACKET, 
				cr_bracket_row_no, 
				cr_bracket_field_no,
				cl_bracket_row_no, 
				(cl_bracket_field_no + BRACKET_SIZE)
				); 
    }
    ASSERTION (cr_bracket_found);

    ASSERTION ((cl_bracket_row_no < cr_bracket_row_no) || ((cl_bracket_row_no == cr_bracket_row_no) && (cl_bracket_field_no < cr_bracket_field_no)));

    start_selected_row_no   = cl_bracket_row_no; 
    start_selected_field_no = cl_bracket_field_no; 

    end_selected_row_no   = cr_bracket_row_no; 
    end_selected_field_no = cr_bracket_field_no + BRACKET_SIZE - 1; 

  } // if (found.front() == cl_couple)


  if (found.front() == ql_couple)
  {
    counter++;
    mode_id = QL_BRACKET_Id;


    ASSERTION (ql_found);

    // -----------------
    bool qr_found = find_token (
				QR_BRACKET, 
				qr_row_no, 
				qr_field_no,
				ql_row_no, 
				ql_field_no + QUOTE_SIZE,
				true
				); 

    ASSERTION (qr_found);
    ASSERTION (qr_row_no == ql_row_no);
    ASSERTION (qr_field_no > ql_field_no);

    start_selected_row_no   = ql_row_no; 
    start_selected_field_no = ql_field_no; 

    end_selected_row_no     = qr_row_no; 
    end_selected_field_no   = qr_field_no + QUOTE_SIZE - 1;


  } // if (found.front() == ql_couple)

  ASSERTION (counter == 1);
  ASSERTION (mode_id != UNDEF_ByteModeId);


  mask_modes (
		row_no_i, 
		field_no_i, 
		start_selected_row_no, 
		start_selected_field_no,
		end_selected_row_no, 
		end_selected_field_no,
		mode_id
		);


ulong        next_row_no; 
ulong        next_field_no; 

const Couple couple (end_selected_row_no, end_selected_field_no);

  if (!couple.get_next(modes_, next_row_no, next_field_no)) 
  {
    return;
  }

  return sign_modes (next_row_no, next_field_no);

}

// ---------
void CountCodeLines::mask_modes (
		ulong      row1_i, 
		ulong      field1_i,
		ulong      row2_i, 
		ulong      field2_i,
		ulong      row3_i, 
		ulong      field3_i,
		ByteModeId mode_id_i
		)
{

ulong delim_size = 0;

  switch (mode_id_i)
  {
    case CPP_BRACKET_Id :
    case CL_BRACKET_Id  :
      delim_size = BRACKET_SIZE;
      break;	   

    case QL_BRACKET_Id  :
      delim_size = QUOTE_SIZE;
      break;	   

    default :
      ASSERTION (0);
      break;  // unused
  }

  ASSERTION (delim_size > 0);


  // ------ 1 ------
bool break_flag = false;

  for (ulong k = row1_i; k < modes_.size(); k++)
  {
    const ulong start_field = ((k == row1_i) ? field1_i : 0);
    for (ulong field = start_field; field < modes_[k].size(); field++)
    {
      if (Couple (k, field) < Couple (row2_i, field2_i))
      {
        modes_[k][field] = LIVING_SPACE_Id;
      }
      else
      {
        break_flag = true;
        break;
      }
    }
    if (break_flag) break;
  }
    
  // ------ 2 ------
  for (ulong s = 0; s < delim_size; s++)
  {
    ASSERTION ((field2_i + s) < modes_[row2_i].size());

    char& the_item = modes_[row2_i][field2_i + s];

    switch (mode_id_i)
    {
      case CPP_BRACKET_Id :
        the_item = CPP_BRACKET_Id;
        break;	   

      case CL_BRACKET_Id  :
        the_item = CL_BRACKET_Id;
        break;	   

      case QL_BRACKET_Id  :
        the_item = QL_BRACKET_Id;
        break;	   

      default :
        ASSERTION (0);
        break;  // unused
    }

  }


  // ------ 3 ------
  for (ulong t = row2_i; t < modes_.size(); t++)
  {
    const ulong start_field = ((t == row2_i) ? (field2_i + delim_size) : 0);
    for (ulong field = start_field; field < modes_[t].size(); field++)
    {
      if (Couple (t, field) <= Couple (row3_i, field3_i))
      {
        switch (mode_id_i)
        {
          case CPP_BRACKET_Id :
          case CL_BRACKET_Id  :
            modes_[t][field] = COMMENT_Id;
            break;	   

          case QL_BRACKET_Id  :
            modes_[t][field] = Q_STRING_Id;
            break;	   

          default :
            ASSERTION (0);
            break;  // unused
        }

      }
      else
      {
        break;
      }
    }
  }


  // ------ 4 ------

  switch (mode_id_i)
  {
    case CPP_BRACKET_Id :
      // Do nothing
      break;	   

    case CL_BRACKET_Id  :
      ASSERTION ((field3_i + 1) >= delim_size);
      for (ulong field = (field3_i - delim_size + 1); field <= field3_i; field++)
      {
        modes_[row3_i][field] = CR_BRACKET_Id;
      } 
      break;	   

    case QL_BRACKET_Id  :
      ASSERTION (field3_i >= delim_size);
      for (ulong field = (field3_i - delim_size + 1); field <= field3_i; field++)
      {
        modes_[row3_i][field] = QR_BRACKET_Id;
      } 
      break;	   

    default :
      ASSERTION (0);
      break;  // unused
  }

}


// ---------
void CountCodeLines::mask2_modes (
		ulong row_i, 
		ulong field_i
		)
{
  for (ulong k = row_i; k < modes_.size(); k++)
  {
    const ulong start_field = ((k == row_i) ? field_i : 0);
    for (ulong field = start_field; field < modes_[k].size(); field++)
    {
      ASSERTION (modes_[k][field] == UNDEF_ByteModeId);
      modes_[k][field] = LIVING_SPACE_Id;
    }
  }

}

// ---------
void CountCodeLines::init_modes ()
{
  for (ulong k = 0; k < rows_.size(); k++)
  {
    modes_.push_back(std::string (rows_[k].size(), UNDEF_ByteModeId));
  }

  ASSERTION (rows_.size() == modes_.size());
  for (ulong k = 0; k < rows_.size(); k++)
  {
    ASSERTION (rows_[k].size() == modes_[k].size());
  }


}


// ---------
bool CountCodeLines::find_token (
		const std::string& token_i, 
		ulong&        row_no_o, 
		ulong&        field_no_o,
		ulong         row_no_i, 
		ulong         field_no_i,
		bool          deny_check_i
		) const
{
  ASSERTION (row_no_i < rows_.size());  
  ASSERTION (field_no_i < rows_[row_no_i].size());  


  if (!deny_check_i)
  {
    for (ulong k = row_no_i; k < rows_.size(); k++)
    {
      const ulong start_field = ((k == row_no_i) ? field_no_i : 0);
      if ((field_no_o = rows_[k].find (token_i, start_field)) != std::string::npos)
      {
        row_no_o = k;
        return true;
      }
    }
  }
  else
  {
    for (ulong k = row_no_i; k < rows_.size(); k++)
    {
      ulong start_field = ((k == row_no_i) ? field_no_i : 0);

      for ( ; start_field < rows_[k].size(); )
      {
        field_no_o = rows_[k].find (token_i, start_field);

	if (field_no_o == std::string::npos) break;

	ASSERTION (field_no_o != std::string::npos);

	ulong slash_count = 0;
	long pos = field_no_o - 1;
        while ((pos >= 0) && (rows_[k][pos] == ONE_SLASH))
        {
          slash_count++;
       	  pos--;
        }

	if (slash_count%2 == 0)
        {
          row_no_o = k;
          return true;
        }
        else
        {
          start_field++;
        }
      }
    }
  }

  row_no_o   = ULONG_MAX;
  field_no_o = ULONG_MAX;

  return false;

}

// ---------
void CountCodeLines::prepare_reported_data ()
{

  for (ulong i = 0; i < modes_.size(); i++)
  {
    triple_.push_back(Triple());
    assert (rows_.size() == modes_.size());
    for (ulong k = 0; k < modes_[i].size(); k++)
    {
      switch (modes_[i][k])
      {
        case LIVING_SPACE_Id :
          if ((rows_[i][k] == SPACE_VALUE) || (rows_[i][k] == TAB_VALUE))
          {
            triple_.back().empty_fields_.push_back(k);
          }
          else
          {
            triple_.back().code_fields_.push_back(k);
          }
          break;

        case CPP_BRACKET_Id  :
        case CL_BRACKET_Id   :
        case CR_BRACKET_Id   :
        case COMMENT_Id      :
          triple_.back().comment_fields_.push_back(k);
          break;

        case QL_BRACKET_Id   :
        case QR_BRACKET_Id   :
        case Q_STRING_Id     :
          triple_.back().code_fields_.push_back(k);
          break;

        default :
          assert(0);
          break;  // unused
      }

    }
    assert ((triple_.back().code_fields_.size() + triple_.back().empty_fields_.size() + triple_.back().comment_fields_.size()) == modes_[i].size());

    all_files_code_fields_s    += triple_.back().code_fields_.size();
    all_files_empty_fields_s   += triple_.back().empty_fields_.size();
    all_files_comment_fields_s += triple_.back().comment_fields_.size();
  }

}



// ---------
void CountCodeLines::Print_Summary_Report (
			const std::string& center_title_i,
			const std::string& left_title_i,

			ulong         lines_code_only_i,
			ulong         lines_code_comment_i,
			ulong         lines_comment_only_i,
			ulong         lines_empty_i,

			ulong         fields_code_i,
			ulong         fields_comment_i,
			ulong         fields_empty_i
			)
{
const ulong total_lines  = lines_code_only_i
                         + lines_code_comment_i
                         + lines_comment_only_i
                         + lines_empty_i;

const ulong total_fields = fields_code_i
                         + fields_comment_i
                         + fields_empty_i;


std::ostringstream oss;
  if (!center_title_i.empty())
  {
    std::cout << std::endl;
    std::cout << std::endl;

    const std::string pref (std::string (max_filenames_size_s, ' '));

    oss.str("");
    oss << "##### " << center_title_i << " #####";

    std::cout << std::string(pref.size(), ' ') << std::string (oss.str().size(), '=') << std::endl;
    std::cout << std::string(pref.size(), ' ') << oss.str() << std::endl;
    std::cout << std::string(pref.size(), ' ') << std::string (oss.str().size(), '=') << std::endl;
    std::cout << std::endl;
  }

  // ----------------------
std::vector<ulong> col_size;
  col_size.push_back(TXT1_SIZE);
  col_size.push_back(ROW_NO_SIZE);
  col_size.push_back(FIELD_NO_SIZE);

  oss.str("");
  oss << std::setw (max_filenames_size_s) 
      << std::left 
      << left_title_i;

const std::vector<bool> align;
std::vector<std::string> row;

std::vector<std::vector<std::string> > header;
  header.push_back(std::vector<std::string>());

  header.back().push_back("");
  header.back().push_back(LINES_TXT0);
  header.back().push_back(BYTES_TXT0);



  // ------ table numbers ------
  {
    std::cout << std::endl;
    SimpleTable table_numbers ("Summary Report (numbers)", col_size, oss.str(), align, true);
  
    table_numbers.build_header (header);
  
    row.clear();
    row.push_back(CODE_ONLY_TXT1);
    row.push_back(to_str(lines_code_only_i));
    row.push_back(to_str(fields_code_i));
    table_numbers.build_row (row);
  
    row.clear();
    row.push_back(CODE_COMMENT_TXT1);
    row.push_back(to_str(lines_code_comment_i));
    row.push_back("-");
    table_numbers.build_row (row);
  
  
    row.clear();
    row.push_back(COMMENT_ONLY_TXT1);
    row.push_back(to_str(lines_comment_only_i));
    row.push_back(to_str(fields_comment_i));
    table_numbers.build_row (row);
  
  
    row.clear();
    row.push_back(EMPTY_TXT1);
    row.push_back(to_str(lines_empty_i));
    row.push_back(to_str(fields_empty_i));
    table_numbers.build_row (row);
  
  
    row.clear();
    row.push_back(TOTAL_TXT1);
    row.push_back(to_str(total_lines));
    row.push_back(to_str(total_fields));
    table_numbers.build_row (row);
  }


  // ------ table percents ------
  {
    double cur_line_percent;
    double cur_field_percent;
    std::ostringstream tss;
    tss.setf(std::ios::fixed, std::ios::floatfield);
    tss.precision(1);

    std::cout << std::endl;
    SimpleTable table_percents ("Summary Report (percents)", col_size, oss.str(), align, true);

    table_percents.build_header (header);

    row.clear();
    row.push_back(CODE_ONLY_TXT1);

    cur_line_percent = (lines_code_only_i*PERCENT_FACTOR)/total_lines;
    tss.str("");
    tss << cur_line_percent;
    tss << PERCENT_SIGN;
    row.push_back(total_lines ? tss.str() : NONE_TXT);

    cur_field_percent = (fields_code_i*PERCENT_FACTOR)/total_fields;
    tss.str("");
    tss << cur_field_percent;
    tss << PERCENT_SIGN;
    row.push_back(total_fields ? tss.str() : NONE_TXT);

    table_percents.build_row (row);


    row.clear();
    row.push_back(CODE_COMMENT_TXT1);

    cur_line_percent = (lines_code_comment_i*PERCENT_FACTOR)/total_lines;
    tss.str("");
    tss << cur_line_percent;
    tss << PERCENT_SIGN;
    row.push_back(total_lines ? tss.str() : NONE_TXT);

    row.push_back("-");

    table_percents.build_row (row);


    row.clear();
    row.push_back(COMMENT_ONLY_TXT1);

    cur_line_percent = (lines_comment_only_i*PERCENT_FACTOR)/total_lines;
    tss.str("");
    tss << cur_line_percent;
    tss << PERCENT_SIGN;
    row.push_back(total_lines ? tss.str() : NONE_TXT);

    cur_field_percent = (fields_comment_i*PERCENT_FACTOR)/total_fields;
    tss.str("");
    tss << cur_field_percent;
    tss << PERCENT_SIGN;
    row.push_back(total_fields ? tss.str() : NONE_TXT);

    table_percents.build_row (row);


    row.clear();
    row.push_back(EMPTY_TXT1);

    cur_line_percent = (lines_empty_i*PERCENT_FACTOR)/total_lines;
    tss.str("");
    tss << cur_line_percent;
    tss << PERCENT_SIGN;
    row.push_back(total_lines ? tss.str() : NONE_TXT);

    cur_field_percent = (fields_empty_i*PERCENT_FACTOR)/total_fields;
    tss.str("");
    tss << cur_field_percent;
    tss << PERCENT_SIGN;
    row.push_back(total_fields ? tss.str() : NONE_TXT);

    table_percents.build_row (row);



    row.clear();
    row.push_back(TOTAL_TXT1);

    cur_line_percent = (total_lines*PERCENT_FACTOR)/total_lines;
    tss.str("");
    tss << std::setprecision (0);
    tss << cur_line_percent;
    tss << PERCENT_SIGN;
    row.push_back(total_lines ? tss.str() : NONE_TXT);

    cur_field_percent = (total_fields*PERCENT_FACTOR)/total_fields;
    tss.str("");
    tss << std::setprecision (0);
    tss << cur_field_percent;
    tss << PERCENT_SIGN;
    row.push_back(total_fields ? tss.str() : NONE_TXT);

    table_percents.build_row (row);

  }

}


// ---------
void CountCodeLines::Show_Summary_Report ()
{
  assert (!filenames_s.empty());
  if (filenames_s.size() == 1) return;

std::ostringstream oss;
  oss << "All " << filenames_s.size() << " files";
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  Print_Summary_Report (
		oss.str(),
		"All files",

		all_files_code_only_lines_s,
		all_files_code_comment_lines_s,
		all_files_comment_only_lines_s,
		all_files_empty_lines_s,

		all_files_code_fields_s,
		all_files_comment_fields_s,
		all_files_empty_fields_s
		);

}



// ---------
void CountCodeLines::show_summary_report (const std::string& prefix_i) const
{
ulong code_only_lines    = 0;
ulong code_comment_lines = 0;
ulong comment_only_lines = 0;
ulong empty_lines        = 0;
const ulong total_lines  = rows_.size();

ulong code_fields    = 0;
ulong comment_fields = 0;
ulong empty_fields   = 0;
ulong total_fields   = 0;


  assert (triple_.size() == total_lines);
  for (ulong k = 0; k < triple_.size(); k++)
  {
    total_fields   += rows_[k].size();

    code_fields    += triple_[k].code_fields_.size();
    comment_fields += triple_[k].comment_fields_.size();
    empty_fields   += triple_[k].empty_fields_.size();

    // ----------------
    if (!triple_[k].code_fields_.empty())
    {
      if (triple_[k].comment_fields_.empty())
      {
        code_only_lines++;
        all_files_code_only_lines_s++;
      }
      else
      {
        code_comment_lines++;
        all_files_code_comment_lines_s++;
      }
      continue;
    }
    assert (triple_[k].code_fields_.empty());


    if (!triple_[k].comment_fields_.empty())
    {
      comment_only_lines++;
      all_files_comment_only_lines_s++;
      continue;
    }
    assert (triple_[k].comment_fields_.empty());

    assert (triple_[k].empty_fields_.size() == rows_[k].size());

    empty_lines++;
    all_files_empty_lines_s++;

  }
  assert (total_lines == (code_only_lines + code_comment_lines + comment_only_lines + empty_lines));
  assert (total_fields == (code_fields + comment_fields + empty_fields));


  Print_Summary_Report (
		"",
		prefix_i,

		code_only_lines,
		code_comment_lines,
		comment_only_lines,
		empty_lines,

		code_fields,
		comment_fields,
		empty_fields
		);

}

// ---------
void CountCodeLines::show_detailed_report (const std::string& prefix_i) const
{
std::ostringstream oss;

const bool detailed_opt1 = 
       count (actual_options_s.begin(), actual_options_s.end(), to_str(DETAILED_OPTION1_ROW));

const bool detailed_opt2 = 
       count (actual_options_s.begin(), actual_options_s.end(), to_str(DETAILED_OPTION2_ROW));

const bool detailed_opt3 = 
       count (actual_options_s.begin(), actual_options_s.end(), to_str(DETAILED_OPTION3_ROW_COL));


const std::string line_txt1 ("Line#");
const std::string byte_txt1 ("* Char");
ulong col1_size = line_txt1.size() + ROW_NO_SIZE;
  if (detailed_opt3)
  {
    col1_size = MAX_VALUE (col1_size, byte_txt1.size() + ROW_NO_SIZE + FIELD_NO_SIZE + 4);
  }
const ulong col2_size = 16;
const ulong col3_size = 7;
const ulong col4_size = col3_size;
const ulong col5_size = col3_size;

  assert (col2_size >= (std::string (CODE_ONLY_TXT1).size()));
  assert (col2_size >= (std::string (CODE_COMMENT_TXT1).size()));
  assert (col2_size >= (std::string (COMMENT_ONLY_TXT1).size()));
  assert (col2_size >= (std::string (EMPTY_TXT1).size()));

  assert (col2_size >= (std::string (CODE_TXT2).size()));
  assert (col2_size >= (std::string (CODE_STRING_TXT2).size()));
  assert (col2_size >= (std::string (COMMENT_TXT2).size()));
  assert (col2_size >= (std::string (COMMENT_BLANK_TXT2).size()));
  assert (col2_size >= (std::string (EMPTY_TXT2).size()));


const std::string pref ((ulong(count(prefix_i.begin(), prefix_i.end(), ' ')) == prefix_i.size()) ? "" : prefix_i);


  std::cout << std::endl;

  // ----------------------
std::vector<ulong> col_size;
  col_size.push_back(col1_size);
  col_size.push_back(col2_size);
  if (detailed_opt2)
  {
    col_size.push_back(col3_size);
    col_size.push_back(col4_size);
    col_size.push_back(col5_size);
  }


std::ostringstream tss, tss2;
  tss << "Detailed Report (";
  if (detailed_opt1) tss2 << "Line Info-1";
  if (detailed_opt2) 
  {
    tss2.str("");
    tss2 << "Line Info-2";
  }
  if (detailed_opt3) 
  {
    tss2.str("");
    tss2 << "Line & Chars Info";
  }
  tss << tss2.str() << ")";

const std::vector<bool> align (2, true);
SimpleTable table (tss.str(), col_size, prefix_i, align);

std::vector<std::vector<std::string> > header;

  header.push_back(std::vector<std::string>());

  header.back().push_back("Line#");
  header.back().push_back("Content");

  if (detailed_opt2)
  {
    header.back().push_back("Code ");
    header.back().push_back("Comment");
    header.back().push_back("Blank");
  }

  if (detailed_opt2)
  {
    header.push_back(std::vector<std::string>());

    header.back().push_back("");
    header.back().push_back("");
    header.back().push_back("Chars");
    header.back().push_back("Chars  ");
    header.back().push_back("Chars");
  }


  table.build_header (header);


  assert (triple_.size() == rows_.size());
  assert (triple_.size() == modes_.size());
  for (ulong k = 0; k < triple_.size(); k++)
  {
    // ----------------
    std::ostringstream tss_col1_line;
    std::ostringstream tss_col2;

    // ----------------
    if (k > 0) 
    {
      if (detailed_opt3) table.build_empty_row();
    }

    tss_col1_line << line_txt1
             << std::setw (ROW_NO_SIZE)
             << std::right
             << (k + 1);

    // ----------------
    if (!triple_[k].code_fields_.empty())
    {
      if (!triple_[k].comment_fields_.empty())
      {
        tss_col2 << CODE_COMMENT_TXT1;
      }
      else
      {
        tss_col2 << CODE_ONLY_TXT1;
      }
    }
    else
    {
      if (!triple_[k].comment_fields_.empty())
      {
        tss_col2 << COMMENT_ONLY_TXT1;
      }
    }

    if (triple_[k].empty_fields_.size() == rows_[k].size())
    {
      tss_col2 << EMPTY_TXT1;
    }

    // ----------------
    std::vector<std::string> row;

    row.push_back(tss_col1_line.str());
    row.push_back(tss_col2.str());

    if (detailed_opt2)
    {
      row.push_back(to_str(triple_[k].code_fields_.size()));
      row.push_back(to_str(triple_[k].comment_fields_.size()));
      row.push_back(to_str(triple_[k].empty_fields_.size()));
    }

    table.build_row (row);

    if (detailed_opt3)
    {
      for (ulong t = 0; t < modes_[k].size(); t++)
      {
        std::ostringstream tss_col1_byte;
        tss_col1_byte << byte_txt1
                      << "["
                      << std::setw (ROW_NO_SIZE)
                      << std::right
                      << (k + 1)
                      << "]"
                      << "["
                      << std::setw (FIELD_NO_SIZE)
                      << std::right
                      << (t + 1)
                      << "]";

        row.clear();
        row.push_back(tss_col1_byte.str());


        ASSERTION (modes_[k][t] < LAST_ByteModeId);
        switch (modes_[k][t])
        {
          case LIVING_SPACE_Id :
            if ((rows_[k][t] == SPACE_VALUE) || (rows_[k][t] == TAB_VALUE))
            {
              row.push_back(EMPTY_TXT2);
            }
            else
            {
              row.push_back(CODE_TXT2);
            }
            break;
  
          case CPP_BRACKET_Id  :
          case CL_BRACKET_Id   :
          case CR_BRACKET_Id   :
          case COMMENT_Id      :
            if ((rows_[k][t] == SPACE_VALUE) || (rows_[k][t] == TAB_VALUE))
            {
              row.push_back(COMMENT_BLANK_TXT2);
            }
            else
            {
              row.push_back(COMMENT_TXT2);
            }
            break;
  
          case QL_BRACKET_Id   :
          case QR_BRACKET_Id   :
          case Q_STRING_Id     :
            row.push_back(CODE_STRING_TXT2);
            break;
  
          default :
            assert (0);
            break; // unused  
        }

        table.build_row (row);
      }
  
    }


  }

}



// ---------
void CountCodeLines::show_report () const
{
  assert (!filenames_s.empty());

  // -----------------------------
std::ostringstream oss;

  oss << std::setw (max_filenames_size_s) 
      << std::left 
      << ((filenames_s.size() == 1) ? "" : filename_.c_str());

const std::string pref (oss.str());

  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;

  oss.str("");
  oss << "### File : " << filename_ << " ###";

  std::cout << std::string(pref.size(), ' ') << std::string (oss.str().size(), '=') << std::endl;
  std::cout << std::string(pref.size(), ' ') << oss.str() << std::endl;
  std::cout << std::string(pref.size(), ' ') << std::string (oss.str().size(), '=') << std::endl;
  std::cout << std::endl;

  create_purified_code ();
  assert (!actual_options_s.empty());

  // ------- summary_report ------
  if (count (actual_options_s.begin(), actual_options_s.end(), to_str(SUMMARY_OPTION)))
  {
    show_summary_report (pref);
  }


  // ------- detailed_report ------
  if (
       count (actual_options_s.begin(), actual_options_s.end(), to_str(DETAILED_OPTION1_ROW))
       || 
       count (actual_options_s.begin(), actual_options_s.end(), to_str(DETAILED_OPTION2_ROW))
       || 
       count (actual_options_s.begin(), actual_options_s.end(), to_str(DETAILED_OPTION3_ROW_COL))
       )
  {
    show_detailed_report (pref);
  }

}


// ---------
bool CountCodeLines::open_file ()
{
  assert (!filename_.empty());

  fin_.open (filename_.c_str());

  if (!fin_)
  {
    std::cerr << ""
         << std::endl
         << "ERROR : Unable to open input file " 
         << filename_ 
         << std::endl;
    return false;
  }

  assert (fin_);
  assert (fin_.is_open());
  return true;
}



// ---------
void CountCodeLines::read_file ()
{
  assert (fin_.is_open());
  assert (rows_.empty());

std::string file_line;
  while (getline (fin_, file_line))
  {
     if ((file_line.size() == 1) && (file_line[0] == CR_VALUE))
	 {
		 rows_.push_back("");
	 }
	 else
	 {
		rows_.push_back (file_line);
     }
  }
}



// --------------
std::string	        CountCodeLines::exe_basename_s;
std::string	        CountCodeLines::exe_full_name_s;
std::vector<std::string>	CountCodeLines::filenames_s;
ulong		CountCodeLines::max_filenames_size_s (0);
std::vector<std::string>	CountCodeLines::actual_options_s;
std::map<std::string, std::vector<std::string> > CountCodeLines::allowed_options_s;

ulong		CountCodeLines::all_files_code_only_lines_s (0);
ulong		CountCodeLines::all_files_code_comment_lines_s (0);
ulong		CountCodeLines::all_files_empty_lines_s (0);
ulong		CountCodeLines::all_files_comment_only_lines_s (0);
ulong		CountCodeLines::all_files_code_fields_s (0);
ulong		CountCodeLines::all_files_empty_fields_s (0);
ulong		CountCodeLines::all_files_comment_fields_s (0);

// --------------
int main (int argc, char** argv)
{
  std::cout << std::endl;
  std::cout << "\tYOUR COMMAND LINE : ";
  for (int i = 0; i < argc; i++) std::cout << argv[i] << " ";
  std::cout << std::endl;

  if (!CountCodeLines::Set_Exe_Filename (argv[0])) return 1;
  CountCodeLines::Init_Allowed_Options ();

  // -------------------------
  CountCodeLines::Set_Default_Option ();
  for (int i = 1; i < argc; i++)
  {
    const std::string str (argv[i]);
    if (str[0] != PRE_OPTION_SIGN)
    {
      CountCodeLines::Add_Filename (str);
      continue;
    }

    if (CountCodeLines::Set_Actual_Options (str)) return 0;
  }

const std::vector<std::string>& filenames = CountCodeLines::Get_Filenames ();

  // -------------------------
  for (ulong i = 0; i < filenames.size(); i++)
  {
    CurFilename_Static = filenames[i];
    CountCodeLines  counter(CurFilename_Static);
    if (!counter.get_open_status()) continue;
  }

  if (CurFilename_Static.empty()) 
  {
    CountCodeLines::Show_Help ();
    return 1;
  }

  CountCodeLines::Show_Summary_Report ();

  return 0;
}
