type t = {
  id: int,
  content: string,
  description: string,
  example: string,
  jsOutput: string
};

let workingReDir = "./snippets/";
let workingJsDir = "./lib/js/snippets/";

let listSnippetNames = () => {
  Node.Fs.readdirSync(workingReDir)
  |> Array.map(name => String.sub(name, 0, String.length(name) - 3));
};

let loadSnippetRawRe = name => {
  Node.Fs.readFileAsUtf8Sync(workingReDir ++ name ++ ".re")
};

let loadSnippetJsOutput = name => {
  Node.Fs.readFileAsUtf8Sync(workingJsDir ++ name ++ ".bs.js");
};

let toJson = snippet => {
  let snippetJson = Js.Dict.empty();
  Js.Dict.set(snippetJson, "id", Js.Json.number(float_of_int(snippet.id)));
  Js.Dict.set(snippetJson, "content", Js.Json.string(snippet.content));
  Js.Dict.set(snippetJson, "description", Js.Json.string(snippet.description));
  Js.Dict.set(snippetJson, "example", Js.Json.string(snippet.example));
  Js.Dict.set(snippetJson, "jsOutput", Js.Json.string(snippet.jsOutput));
  Js.Json.object_(snippetJson);
};

let loadSnippets = () => {
  listSnippetNames()
  |> Array.map(name => (loadSnippetRawRe(name), loadSnippetJsOutput(name)))
  |> Array.mapi((i, (rawRe, jsOutput)) => {
    id: i,
    content: rawRe,
    description: "description",
    example: "example",
    jsOutput
  })
};

