import utils::*;

class tb_config extends BaseObj;

    string firmware;
    string rodata;
    string testname;

    function new(Logger logger);
        super.new(logger);
    endfunction

    function parse_args();


    endfunction

endclass
