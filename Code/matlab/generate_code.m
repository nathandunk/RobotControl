function cpp = generate_code(x,var_str)

cpp = ccode(x);

if (min(size(x)) == 1)
cpp = strrep(cpp,'x[',[var_str '[']);
cpp = strrep(cpp,'][0]',']');    
else
cpp = strrep(cpp,'x[',[var_str '(']);
cpp = strrep(cpp,'][',',');
cpp = strrep(cpp,']',')');
end

end