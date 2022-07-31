import sys
import re
import functs
           
def main():
            d={}
            while True:
                        try:
                                    line  = sys.stdin.readline()
                                    if len(line)==0:
                                                sys.exit(0)
                                    elif line=="\n" or len(line.strip())==0:
                                                functs.Exception1('Ivalid input. Please enter the command(a/c/r), street name (Alphabetical and space characters only) and coordinates separated by space.')
                                    else:            
                                                cmd = functs.input_cmd(line)                                    
                                                if cmd.lower() not in ['a','c','r','g']:
                                                            functs.Exception1('Ivalid input.Please enter the command as "a" or "c" or "r".')
                                                elif cmd.lower() =='a' and len(re.findall(r'\w\s"[a-zA-Z ]+"\s\(\s*-*\s*\d+\s*,\s*-*\s*\d+\s*\)\s*\(\s*-*\s*\d+\s*,\s*-*\s*\d+\s*\)',line))!=0:
                                                            d=functs.addition(line,d)
                                                elif cmd.lower() =='c' and len(re.findall(r'\w\s"[a-zA-Z ]+"\s\(\s*-*\s*\d+\s*,\s*-*\s*\d+\s*\)\s*\(\s*-*\s*\d+\s*,\s*-*\s*\d+\s*\)',line))!=0:
                                                            d=functs.change(line,d)
                                                elif cmd.lower() =='r' and re.match(r'\w\s"[a-zA-Z ]+"$',line)!=None:
                                                            d=functs.remove(line,d)
                                                elif cmd.lower() =='g' and len(line.strip())==1:
                                                            d=functs.vertex_edge(d)                                                            
                                                else:
                                                            functs.Exception1('Ivalid input. Please enter the command(a/c/r), street name (Alphabetical and space characters only) and coordinates separated by space.')

                        except KeyboardInterrupt:
                                    print('\nError: Keyboard interrupt exception.')
                        except SyntaxError:
                                    functs.Exception1('Ivalid input. Please enter the command(a/c/r), street name (Alphabetical and space characters only) and coordinates separated by space.')
                        except ZeroDivisionError:
                                    functs.Exception1('Ivalid input. Please enter the command(a/c/r), street name (Alphabetical and space characters only) and coordinates separated by space.')
                        except EOFError:
                                    sys.exit(0)
        

if __name__ == '__main__':
    main()
