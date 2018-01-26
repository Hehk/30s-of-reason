module Client = {
  type t;
};

[@bs.module] external algoliasearch : (string, string) => Client.t = "";

let make = (~applicationId, ~apiKey, ()) => algoliasearch(applicationId, apiKey);

module Index = {
  type t;
  [@bs.send.pipe : Client.t] external initIndex : string => t = "initIndex";
  let make = (name, algoliaClient) => algoliaClient |> initIndex(name);
  [@bs.send.pipe : t] external addObjects : array(Js.t({..})) => Js.Promise.t('res) = "addObjects";
  [@bs.send.pipe : t] external search : Js.t({..}) => Js.Promise.t('res) = "search";
};
