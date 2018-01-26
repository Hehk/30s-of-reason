type response('a) = {
  .
  "hits": array('a),
  "page": int,
  "nbHits": int,
  "nbPages": int,
  "hitsPerPage": int,
  "processingTimeMS": int,
  "exhaustiveNbHits": bool,
  "query": string,
  "queryAfterRemoval": Js.Nullable.t(string),
  "params": Js.Nullable.t(string),
  "message": Js.Nullable.t(string),
  "aroundLatLng": Js.Nullable.t(string),
  "automaticRadius": Js.Nullable.t(int),
  "serverUsed": Js.Nullable.t(string),
  "parsedQuery": Js.Nullable.t(string),
  "facets": Js.Nullable.t(Js.t({.})),
  "facets_stats": Js.Nullable.t(Js.t({.}))
};

module Client = {
  type t;
  [@bs.send.pipe : t] external search : array(Js.t({..})) => Js.Promise.t('groupResponse) = "search";
  [@bs.send.pipe : t] external batch : array(Js.t({..})) => Js.Promise.t('groupResponse) = "batch";

  [@bs.module] external algoliasearch : (string, string) => t = "";
  let make = (~applicationId, ~apiKey, ()) => algoliasearch(applicationId, apiKey);
};

module Index = {
  type t;
  [@bs.send.pipe : Client.t] external initIndex : string => t = "initIndex";
  let make = (name, algoliaClient) => algoliaClient |> initIndex(name);
  [@bs.send.pipe : t] external search : Js.t({..}) => Js.Promise.t(response('a)) = "search";
  [@bs.send.pipe : t] external searchForFacetValues : Js.t({..}) => Js.Promise.t(response('a)) =
    "searchForFacetValues";
  /* fun browseAll -- not implemented */
  [@bs.send.pipe : t] external addObjects : array(Js.t({..})) => Js.Promise.t(response('a)) = "addObjects";
  [@bs.send.pipe : t] external saveObjects : array(Js.t({..})) => Js.Promise.t(response('a)) = "saveObjects";
  [@bs.send.pipe : t] external partialUpdateObjects : array(Js.t({..})) => Js.Promise.t(response('a)) =
    "partialUpdateObjects";
  [@bs.send.pipe : t] external deleteObjects : array(string) => Js.Promise.t(response('a)) = "deleteObjects";
  [@bs.send.pipe : t] external deleteBy : string => Js.Promise.t(response('a)) = "deleteBy";
  [@bs.send.pipe : t] external getObjects : string => Js.Promise.t(response('a)) = "getObjects";
  /* fun waitTask() -- not implemented*/
};


