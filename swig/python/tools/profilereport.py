import sys
import re

import argparse

try:
  import pydot
except:
  raise Exception("To use the functionality of casadi.tools.graph, you need to have pydot Installed. Try `easy_install pydot`.")  
      

descr = """
This tool reads raw profile_log data (recorded in casadi with `CasadiOptions.startProfiling()`)
and creates an interactive webpage with the results.
"""

parser = argparse.ArgumentParser(description=descr,usage='python -mcasadi.tools.profilereport [-o OUTPUT] profile_log')
parser.add_argument('profile_log', type=argparse.FileType('r'),help='The filename of the raw profile_log as generated by casadi')
parser.add_argument("-o",dest="output",type=argparse.FileType('w'), help='html file to write report to')

args = parser.parse_args()

out = sys.stdout if args.output is None else args.output
f = args.profile_log

functiondict = {}

linereg = re.compile("^([\d\.]+) ns \| ([\d\.]+) ms \| (0x[\w\d]+:[\w_]+):(\d+)\|(0x[\w\d]+:[\w_]+)?\|(.*)$")

startreg = re.compile("^start (0x[\w\d]+:[\w_]+)$")

overheadreg = re.compile("^overhead (0x[\w\d]+:[\w_]+)\|([\d\.]+) ns$")

def parseline(line):
  m = re.match(linereg,line)
  if m:
    return (float(m.group(1))*1e-6, float(m.group(2))*1e-3, m.group(3), int(m.group(4)), m.group(5) , m.group(6) )
  else:
    return None
    
def parsestart(line):
  m = re.match(startreg,line)
  if m:
    return m.group(1),
  else:
    return None
    
def parseoverhead(line):
  m = re.match(overheadreg,line)
  if m:
    return (m.group(1),float(m.group(2))*1e-6)
  else:
    return None
    
for l in f:
  r = parseline(l)
  if r is None:
    r = parsestart(l)
    if r is None: 
      r = parseoverhead(l)
      if r is None: continue
      idn, overhead = r
      if idn not in functiondict: continue
      functiondict[idn]["overhead"].append(overhead)
    else:
      idn, = r
      if idn in functiondict:
        functiondict[idn]["ncalls"]+=1
      else:
        functiondict[idn] = {"sourcecode" : [], "ncalls": 1, "localtimes": [], "idnlinks": [], "overhead":[] }
  else:
    local , cumul, idn, loc, idnlink ,code = r
    if loc >= len(functiondict[idn]["sourcecode"]):
      n = loc - len(functiondict[idn]["sourcecode"])+1
      functiondict[idn]["sourcecode"].extend([""]*n)
      functiondict[idn]["localtimes"].extend([[] for i in range(n)])
      functiondict[idn]["idnlinks"].extend([None]*n)
      functiondict[idn]["sourcecode"][loc] = code
      functiondict[idn]["idnlinks"][loc] = idnlink
    
    functiondict[idn]["localtimes"][loc].append(local)

out.write("""
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
  <body>
   <img src="callgraph.png"/>
""")

for k,v in functiondict.iteritems():
  v["localtimes_sum"] = [sum(i) for i  in v["localtimes"]]
  assert(len(v["sourcecode"])==len(v["localtimes"]))
  assert(len(v["sourcecode"])==len(v["idnlinks"]))
  

for k,v in functiondict.iteritems():
  v["localtime_sum_internal"] = sum([localtime for idnlink, localtime  in zip(v["idnlinks"],v["localtimes_sum"]) if idnlink is None] )
  v["localtime_sum_external"] = sum([localtime for idnlink, localtime  in zip(v["idnlinks"],v["localtimes_sum"]) if idnlink is not None])
  v["localtime_sum_overhead"] = sum(v["overhead"])
  v["localtime_sum_total"] = sum(v["localtimes_sum"])+v["localtime_sum_overhead"] 
  v["calls"] = set(filter(lambda x: x is not None,v["idnlinks"]))
  
  
graph = pydot.Dot('G', graph_type='digraph',rankdir="LR")
for k,v in functiondict.iteritems():
  graph.add_node(pydot.Node("node" + k.replace(':','_'),label=" %s | %d -- %.5f s | %.5f s -- %.5f s -- %.5f s " % (k,v["ncalls"],v["localtime_sum_total"],v["localtime_sum_internal"],v["localtime_sum_external"],v["localtime_sum_overhead"]) ,shape="record"))
  for c in v["calls"]:
    s = sum([len(localtimes) for idnlink, localtimes  in zip(v["idnlinks"],v["localtimes"]) if idnlink==c])
    graph.add_edge(pydot.Edge("node" + k.replace(':','_'),"node" + c.replace(':','_'),label="%d" % s))
graph.write_png("callgraph.png")
  
localtime_internal_total = sum(v["localtime_sum_internal"] for k,v in functiondict.iteritems())
localtime_overhead_total = sum(v["localtime_sum_overhead"] for k,v in functiondict.iteritems())


out.write("<table><thead><tr><th>Id</th><th>#calls</th><th>Total (s)</th><th>Internal (s)</th><th>External (s)</th><th>Overhead (s)</th></tr></thead>\n")
for k,v in functiondict.iteritems():
  out.write("<tr><td><a href='#%s'>%s</a></td><td>%d</td><td>%.5f</td><td>%.5f</td><td>%.5f</td><td>%.5f</td></tr>\n" % (k,k,v["ncalls"],v["localtime_sum_total"],v["localtime_sum_internal"],v["localtime_sum_external"],v["localtime_sum_overhead"]))
out.write("<tr><th>Sum MX</th><th>/</th><th>/</th><th>%.5f</th><th>/</th><th>%.5f</th></tr>\n" % (localtime_internal_total, localtime_overhead_total))
out.write("</table>\n")
  
for k,v in functiondict.iteritems():
  out.write("<a name='%s'><h2>%s</h2></a><dl><dt>#calls</dt><dd>%d</dd><dt>Total (s)</dt><dd>%.5f</dd><dt>Internal (s)</dt><dd>%.5f</dd><dt>External (s)</dt><dd>%.5f</dd><dt>Overhead (s)</dt><dd>%.5f</dd></dl>\n" % (k,k,v["ncalls"],v["localtime_sum_total"],v["localtime_sum_internal"],v["localtime_sum_external"],v["localtime_sum_overhead"]))
  out.write("<table><thead><tr><th>Codeline</th><th>total (ms)</th><th>ncalls</th><th>souce</th></tr></thead>\n")
  for i,s in enumerate(v["sourcecode"]):
    if v["idnlinks"][i] is not None:
      s = "<a href='#%s'>%s</a>" % (v["idnlinks"][i],s)
    out.write("<tr><td>%d</td><td>%.5f</td><td>%d</td><td>%s</td></tr>\n" % (i,sum(v["localtimes"][i])*1e3,len(v["localtimes"][i]),s))
  out.write("</table>\n")
    
out.write("""
  </body>
</html>
""")
